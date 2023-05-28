// Fill out your copyright notice in the Description page of Project Settings.


#include "MulliganPhase.h"
#include "Card.h"
#include "MatchHUDBase.h"

void UMulliganPhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	StartMulligan();
}

bool UMulliganPhase::EndIf()
{
	for (const auto Controller : GameContext.GameControllersArray)
	{
		if(Controller && !Controller->GetMatchHud()->MulliganEnded)
		{
			return false;
		}
	}
	return true;
}

void UMulliganPhase::UpdatePhase(float Delta)
{
	Super::UpdatePhase(Delta);
	const auto GameState = GameContext.GameState;
	if(GameState->TurnTime < MulliganMaxTime)
	{
		GameState->TurnTime+=Delta;
		if(GameState->TurnTime >= MulliganMaxTime)
		{
			for (const auto Controller : GameContext.GameControllersArray)
			{
				if(Controller && !Controller->GetMatchHud()->MulliganEnded)
				{
					Controller->GetMatchHud()->GetMulliganReplaceCards();
				}
			}
		}
	}
}

void UMulliganPhase::StartMulligan()
{
	GameContext.GameState->TurnTime =0;
	GameContext.GameState->TurnMaxTime =MulliganMaxTime;
	for (const auto Controller : GameContext.GameControllersArray)
	{
		if(Controller)
		{
			TArray<UCardPreset*> MulliganCards;
			for(int i =0; i < GameContext.GameMode->NumPlayersCardBegin;i++)
			{
				const auto Card = Controller->PlayerStateRef->DeckHolder[i];
				if(Card != nullptr)
					MulliganCards.Add(Card->GetPreset());
			}
			Controller->GetMatchHud()->ShowMulliganCards(MulliganCards);
		}
	}
}
