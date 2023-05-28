// Fill out your copyright notice in the Description page of Project Settings.


#include "EndMatchmakingPhase.h"

void UEndMatchmakingPhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	EndMatchmakingScreen();
}

bool UEndMatchmakingPhase::EndIf()
{
	for (const auto Controller : GameContext.GameControllersArray)
	{
		if(Controller && !Controller->MatchmakingTransitionEnded)
		{
			return false;
		}
	}
	return true;
}

void UEndMatchmakingPhase::EndMatchmakingScreen()
{
	for (auto item : GameContext.GameControllersArray)
	{
		AMatchPlayerController* Other = *GameContext.GameControllersArray.FindByPredicate(
			[item](const AMatchPlayerController* c)
			{
				return c != item;
			});
				
		if(Other != nullptr)
		{
			const AMatchPlayerController* Opponent = Other;
			AMatchPlayerController* MainPlayer  = item;
			if(Opponent != nullptr && MainPlayer != nullptr)
			{
				MainPlayer->ShowOpponentInMatchmaking(MainPlayer->PlayerStateRef->PlayerStatus,Opponent->PlayerStateRef->PlayerStatus);
			}
		}
	}
}
