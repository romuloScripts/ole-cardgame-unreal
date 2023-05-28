// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamFormationPhase.h"
#include "GameStateEnums.h"
#include "Board.h"
#include "MatchHUDBase.h"
#include "RulesFunctionLibrary.h"

void UTeamFormationPhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	GameContext.GameState->TurnTime =0;
	GameContext.GameState->TurnMaxTime = TeamFormationMaxTime;
	GameContext.GameState->GetBoard()->OnMoveBegin.AddDynamic(this,&ThisClass::OnMoveBegin);
	GameContext.GameState->GetBoard()->OnMoveEnd.AddDynamic(this,&ThisClass::OnMoveEnd);
	
	if(GameContext.GameState->GetBoard())
	{
		GameContext.GameState->GetBoard()->SpawnSoccerPlayers(URulesFunctionLibrary::GetBoardPlayersData(GameContext.PlayerStates));
	}
	PlayersRemainingConfirmation = GameContext.GameControllersArray;
	for (const auto Controller : PlayersRemainingConfirmation)
	{
		Controller->GetMatchHud()->ShowTeamFormation();
		Controller->PlayerStateRef->SetMoveState(ETurnMoveState::WaitMoveFormation);
	}
}

bool UTeamFormationPhase::PlayersConfirmed() const
{
	return PlayersRemainingConfirmation.Num()<=0;
}

bool UTeamFormationPhase::TurnEnded() const
{
	return GameContext.GameState->TurnTime >= TeamFormationMaxTime;
}

bool UTeamFormationPhase::EndIf()
{
	if(GameContext.GameState->InMovement()) return false;
	return TurnEnded() || PlayersConfirmed();
}

void UTeamFormationPhase::OnEnd()
{
	Super::OnEnd();
	GameContext.GameState->GetBoard()->OnMoveBegin.RemoveDynamic(this,&UTeamFormationPhase::OnMoveBegin);
	GameContext.GameState->GetBoard()->OnMoveEnd.RemoveDynamic(this,&UTeamFormationPhase::OnMoveEnd);
	for (const auto Controller : GameContext.GameControllersArray)
	{
		Controller->DisableAllInteractions();
		Controller->GetMatchHud()->RemoveTeamFormation();
	}
}

void UTeamFormationPhase::UpdatePhase(float Delta)
{
	Super::UpdatePhase(Delta);

	for (int i = PlayersRemainingConfirmation.Num() -1; i >=0;i--)
	{
		if(PlayersRemainingConfirmation[i]->EndTurnRequested)
		{
			PlayersRemainingConfirmation[i]->DisableAllInteractions();
			PlayersRemainingConfirmation[i]->GetMatchHud()->RemoveTeamFormation();
			PlayersRemainingConfirmation.RemoveAt(i);
		}
	}

	const auto GameState = GameContext.GameState;
	if(GameState->TurnTime < TeamFormationMaxTime)
	{
		GameState->TurnTime+=Delta;
	}
}

void UTeamFormationPhase::OnMoveBegin(int Player)
{
	GameContext.PlayerStates[Player]->MoveBegin();
}

void UTeamFormationPhase::OnMoveEnd(const int Player)
{
	GameContext.PlayerStates[Player]->MoveEnded();
	for (int i = 0; i < PlayersRemainingConfirmation.Num();i++)
	{
		if(PlayersRemainingConfirmation[i]->GetId() == Player)
		{
			PlayersRemainingConfirmation[i]->PlayerStateRef->SetMoveState(ETurnMoveState::WaitMoveFormation);
			break;
		}
	}
}
