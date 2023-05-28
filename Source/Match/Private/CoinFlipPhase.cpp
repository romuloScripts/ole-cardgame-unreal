// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinFlipPhase.h"

#include "MatchHUDBase.h"

void UCoinFlipPhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	CoinFlip();
}

bool UCoinFlipPhase::EndIf()
{
	for (const auto Controller : GameContext.GameControllersArray)
	{
		if(Controller && !Controller->GetMatchHud()->CoinFlipEnded)
		{
			return false;
		}
	}
	return true;
}

void UCoinFlipPhase::CoinFlip()
{
	const int NumPlayers = GameContext.GameControllersArray.Num();
	const int First = FMath::RandRange(0,NumPlayers-1);
	GameContext.GameState->CurrentTurnPlayer = First;

	for (int i =0;i< NumPlayers;i++)
	{
		const auto Player = GameContext.GameControllersArray[i];
		if(Player && Player->GetMatchHud())
		{
			Player->GetMatchHud()->ShowFlipCoinScreen(i==First);
		}
	}
}