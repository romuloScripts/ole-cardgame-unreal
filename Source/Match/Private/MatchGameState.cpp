// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchGameState.h"
#include "Board.h"
#include "MatchPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "BoardFunctionLibrary.h"
#include "RulesFunctionLibrary.h"

void AMatchGameState::SetWinner_Implementation(int WinnerId)
{
	WinnerPlayerId = WinnerId;
	WinState = EWinState::Win;
	AddTurnCount();
}

void AMatchGameState::SetDraw_Implementation()
{
	WinnerPlayerId = -1;
	WinState = EWinState::Draw;
	AddTurnCount();
}

void AMatchGameState::OnRep_TurnsUpdated()
{
	OnTurnChanged.Broadcast();
}

void AMatchGameState::AddCardToGraveyard(UCard* Card,bool UsedCard)
{
	Graveyard.AddUnique(Card);
	if(UsedCard) OnCardUsed.Broadcast(Card);
	OnRep_GraveyardUpdated();
}

ABoard* AMatchGameState::GetBoard()
{
	if(Board == nullptr) SetBoard(UBoardFunctionLibrary::GetBoard(this));
	return Board;
}

void AMatchGameState::OnRep_GraveyardUpdated() const
{
	OnGraveyardUpdate.Broadcast(Graveyard);
}

void AMatchGameState::SetSurrender_Implementation(int SurrenderId)
{
	if(WinState != EWinState::None) return;
	WinnerPlayerId = SurrenderId == 0 ? 1 : 0;
	WinState = EWinState::Surrender;
}

AMatchPlayerState* AMatchGameState::GetPlayerStateById(const int Id)
{
	return PlayersStateArray[Id];
}

EWinState AMatchGameState::GetWinState() const
{
	return WinState;
}

int AMatchGameState::GetWinnerPlayerId() const
{
	return WinnerPlayerId;
}

void AMatchGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMatchGameState, Board);
	DOREPLIFETIME(AMatchGameState, CurrentTurnPlayer);
	DOREPLIFETIME(AMatchGameState, TurnTime);
	DOREPLIFETIME(AMatchGameState, TurnMaxTime);
	DOREPLIFETIME(AMatchGameState, PlayersStateArray);
	DOREPLIFETIME(AMatchGameState, WinState);
	DOREPLIFETIME(AMatchGameState, WinnerPlayerId);
	DOREPLIFETIME(AMatchGameState, TotalTurns);
	DOREPLIFETIME(AMatchGameState, MaxTurns);
	DOREPLIFETIME(AMatchGameState, MaxCardsInHands);
	DOREPLIFETIME(AMatchGameState, Graveyard);
}

void AMatchGameState::SetPlayerStates(TArray<AMatchPlayerState*> Array, const int MaxMana, const int StartMana)
{
	if(Board == nullptr) SetBoard(UBoardFunctionLibrary::GetBoard(this));
	TArray<FPlayerStatus> PlayerStatuses;
	for (const auto PlayerState : Array)
	{
		PlayerStatuses.Add(PlayerState->PlayerStatus);
	}
	const bool ActiveReserveColor = UBoardFunctionLibrary::GetPlayersUseSameColor(PlayerStatuses);
	for (const auto PlayerState : Array)
	{
		PlayerState->InitMana(MaxMana,StartMana);
		PlayerState->ShuffleCards();
		const int BoardId = PlayersStateArray.Num();
		PlayerState->BoardPlayerId = BoardId;
		PlayersStateArray.Add(PlayerState);
		const bool UseReserveColor = ActiveReserveColor && BoardId != 0;
		if(UseReserveColor)
		{
			PlayerState->SetUseReserveColor();
		}
	}
}

void AMatchGameState::AddTurnCount()
{
	TotalTurns++;
	OnRep_TurnsUpdated();
}

void AMatchGameState::NextTurn()
{
	AddTurnCount();
	CurrentTurnPlayer++;
	CurrentTurnPlayer %= PlayersStateArray.Num();
	StartTurn();
	ResetUnitsInactiveStatus();
	GetCurrentTurnPlayerState()->AddStartTurnMana(1);
	GetCurrentTurnPlayerState()->ResetMana();
	GetCurrentTurnPlayerState()->DrawCardsFromTop(1);
}

void AMatchGameState::StartTurn()
{
	TurnTime =0;
	OnTurnStartEvent(CurrentTurnPlayer);
	GetCurrentTurnPlayerState()->SetMoveState(ETurnMoveState::WaitMoveBattle);
}

void AMatchGameState::PlayersDrawCards(int Amount)
{
	for (const auto Player : PlayersStateArray)
	{
		Player->DrawCardsFromTop(Amount);
	}
}

void AMatchGameState::ResetUnitsInactiveStatus() const
{
	Board->ResetUnitsInactiveStatus();
}

AMatchPlayerState* AMatchGameState::GetCurrentTurnPlayerState() const
{
	return PlayersStateArray[CurrentTurnPlayer];
}

AMatchPlayerState* AMatchGameState::GetOpponentPlayerState(AMatchPlayerState* PlayerState)
{
	return  PlayersStateArray[(PlayerState->BoardPlayerId+1)%PlayersStateArray.Num()];
}

void AMatchGameState::BeginPlay()
{
	Super::BeginPlay();
	if(Board == nullptr) SetBoard(UBoardFunctionLibrary::GetBoard(this));
}

void AMatchGameState::SetMaxTurns(int Max)
{
	MaxTurns = Max;
}

void AMatchGameState::SetBoard(ABoard* NewBoard)
{
	Board = NewBoard;
}

bool AMatchGameState::InMovement()
{
	for (const auto Player : PlayersStateArray)
	{
		if(!Player->InMovement()) return false;
	}
	return true;
}

void AMatchGameState::OnTurnStartEvent_Implementation(int PlayerId)
{
	OnTurnStarted.Broadcast(PlayerId);
}
