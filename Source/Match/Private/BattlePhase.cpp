// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePhase.h"
#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "RulesFunctionLibrary.h"
#include "MatchPlayerController.h"
#include "MatchPlayerState.h"
#include "MatchGameState.h"
#include "MatchGameMode.h"
#include "Card.h"
#include "MatchHUDBase.h"

void UBattlePhase::StartTurn()
{
	GameContext.GetCurrentTurnPlayerController()->StartTurn();
}

void UBattlePhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	StartBoard();
	StartControllers();
	GameContext.GameState->MaxCardsInHands = GameContext.GameMode->MaxCardsInHands;
	GameContext.GameState->TurnMaxTime = GameContext.GameMode->MaxTurnTimeSeconds;
	GameContext.GameState->OnCardUsed.AddDynamic(this,&UBattlePhase::OnCardUsed);
	GameContext.GameState->GetBoard()->OnMoveBegin.AddDynamic(this,&UBattlePhase::OnMoveBegin);
	GameContext.GameState->GetBoard()->OnMoveEnd.AddDynamic(this,&UBattlePhase::OnMoveEnd);
	GameContext.GameState->GetBoard()->OnGoal.AddDynamic(this,&UBattlePhase::OnGoal);
	GameContext.GameState->PlayersDrawCards(GameContext.GameMode->NumPlayersCardBegin);
	GameContext.GameState->StartTurn();
	StartTurn();
}

bool UBattlePhase::EndIf()
{
	return GameContext.GameState->GetWinState() != EWinState::None;
}

void UBattlePhase::TurnCountdown(float Delta)
{
	GameContext.GameState->TurnTime += Delta;
	if(!GameContext.GameState->InMovement() && EndTurnByTime())
	{
		SetVictory();
		if(!EndIf())
		{
			if(UBoardFunctionLibrary::BallInPossesOfGoalkeeper(
				GameContext.GameState->GetBoard(),GameContext.GetCurrentTurnPlayerState()->BoardPlayerId))
			{
				GoalkeeperHeldBall1Turn = true;
			}
			NextTurn();
		}
	}else{
		GameContext.GetCurrentTurnPlayerController()->EndTurnRequested = false;
	}
}

bool UBattlePhase::GoalEnded()
{
	for (const auto PlayerController : GameContext.GameControllersArray)
	{
		if(!PlayerController->GetMatchHud()->GoalScreenEnded) return false;
	}
	return true;
}

void UBattlePhase::WaitGoalEnd()
{
	if(WaitGoalScreenEnd && GoalEnded())
	{
		for (const auto PlayerController : GameContext.GameControllersArray)
		{
			PlayerController->GetMatchHud()->GoalScreenEnded = false;
		}
		WaitGoalScreenEnd = false;
		OnMoveEnd(GameContext.GetCurrentTurnPlayerState()->BoardPlayerId);
	}
}

void UBattlePhase::UpdatePhase(float Delta)
{
	Super::UpdatePhase(Delta);
	
	if(GoalHappened)
	{
		WaitGoalEnd();
		return;
	} 
	TurnCountdown(Delta);
}

void UBattlePhase::StartControllers()
{
	for (const auto Controller : GameContext.GameControllersArray)
	{
		Controller->BattleStarted();
	}
}

void UBattlePhase::OnEnd()
{
	Super::OnEnd();
	GameContext.GameState->OnCardUsed.RemoveDynamic(this,&UBattlePhase::OnCardUsed);
	GameContext.GameState->GetBoard()->OnMoveBegin.RemoveDynamic(this,&UBattlePhase::OnMoveBegin);
	GameContext.GameState->GetBoard()->OnMoveEnd.RemoveDynamic(this,&UBattlePhase::OnMoveEnd);
	GameContext.GameState->GetBoard()->OnGoal.RemoveDynamic(this,&UBattlePhase::OnGoal);
	const auto Board = GameContext.GameState->GetBoard();
	if(!Board) return;
	for (const auto Unit : Board->GetAllUnits())
	{
		Unit->OnRedCardReceived.RemoveDynamic(this,&UBattlePhase::OnRedCard);
	}
}

void UBattlePhase::StartBoard() const
{
	const auto Board = GameContext.GameState->GetBoard();
	if(!Board) return;
	Board->StartPlayers(URulesFunctionLibrary::GetBoardPlayersData(GameContext.PlayerStates));
	Board->StartBall(GameContext.GameState->CurrentTurnPlayer);
	for (const auto Unit : Board->GetAllUnits())
	{
		Unit->OnRedCardReceived.AddDynamic(this,&UBattlePhase::OnRedCard);
	}
}

void UBattlePhase::OnRedCard(AUnitActor* UnitActor)
{
	if(const auto Board = GameContext.GameState->GetBoard()) Board->RemoveUnit(UnitActor);
	for (const auto PlayerController : GameContext.GameControllersArray)
	{
		PlayerController->GetMatchHud()->ShowRedCardMessage(UnitActor->CardPreset,UnitActor->GetPlayerId() != PlayerController->GetId());
	}
	const auto PlayerState = Cast<AMatchPlayerState>(UnitActor->GetOwnerPlayerState());
	if(PlayerState) PlayerState->RemoveAllCardsOfPreset(UnitActor->CardPreset);
}

void UBattlePhase::NextTurn()
{
	GameContext.GetCurrentTurnPlayerController()->DisableAllInteractions();
	GameContext.GameState->NextTurn();
	if(GoalHappened  || GoalkeeperHeldBall1Turn)
	{
		GameContext.GameState->GetBoard()->StartBall(GameContext.GameState->CurrentTurnPlayer);
		GoalHappened = false;
		GoalkeeperHeldBall1Turn = false;
	}
	StartTurn();
}

bool UBattlePhase::EndTurn()
{
	return EndTurnByTime() || EndTurnByMove();
}

bool UBattlePhase::EndTurnByTime()
{
	return GameContext.GameState->TurnTime >= GameContext.GameState->TurnMaxTime ||
		GameContext.GetCurrentTurnPlayerController()->EndTurnRequested;
}

bool UBattlePhase::EndTurnByMove() const
{
	return GoalHappened || URulesFunctionLibrary::TurnEndedByMoves(GameContext.GameState);
}

bool UBattlePhase::BattleTimeEnd()
{
	return EndTurn() && GameContext.GameState->TotalTurns >= (GameContext.GameMode->MaxTurns-1);
}

void UBattlePhase::OnMoveEnd(int Player)
{
	GameContext.PlayerStates[Player]->MoveEnded();
	if(WaitGoalScreenEnd) return;
	SetVictory();
	if(EndIf()) return;
	
	if(EndTurnByMove())
	{
		NextTurn();
	}else
	{
		GameContext.GetCurrentTurnPlayerState()->SetMoveState(ETurnMoveState::WaitMoveBattle);
	}
}

void UBattlePhase::OnMoveBegin(int Player)
{
	GameContext.PlayerStates[Player]->MoveBegin();
}

void UBattlePhase::OnCardUsed(UCard* Card)
{
	if(EndTurnByMove())
	{
		SetVictory();
		if(EndIf()) return;
		NextTurn();
	}
}

void UBattlePhase::OnGoal(int PlayerId)
{
	GameContext.PlayerStates[PlayerId]->AddGoal();
	GoalHappened = true;
	WaitGoalScreenEnd = true;
	for (const auto PlayerController : GameContext.GameControllersArray)
	{
		PlayerController->DisableAllInteractions();
		PlayerController->GetMatchHud()->GoalScreen(PlayerId);
	}
}

void UBattlePhase::SetVictory()
{
	int Winner = URulesFunctionLibrary::GetWinnerId(GameContext.PlayerStates,GameContext.GameState,GameContext.GameMode);
	if(Winner>=0)
	{
		GameContext.GameState->SetWinner(Winner);
	}else if(BattleTimeEnd())
	{
		Winner = URulesFunctionLibrary::GetBetterScore(GameContext.GameState);
		if(Winner>=0)
		{
			GameContext.GameState->SetWinner(Winner);
		}else
		{
			GameContext.GameState->SetDraw();
		}
	}
}

