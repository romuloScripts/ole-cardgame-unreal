// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBackHand.h"

#include "CardBackInHand.h"

void UCardBackHand::SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card)
{
	Super::SetupCard(CardVisual, Card);
	const auto CardBack = Cast<UCardBackInHand>(CardVisual);
	CardBack->SetupCardBack(PlayerStatus.CardBack,PlayerStatus.ColorPalette,PlayerStatus.UseReserveColor);
}

TSubclassOf<UCardInHandWidgetBase> UCardBackHand::GetCardClass()
{
	return CardInHandClass;
}

void UCardBackHand::SetStatus(FPlayerStatus NewPlayerStatus)
{
	Super::SetStatus(NewPlayerStatus);
	for(const auto CardItem : CardsOrder)
	{
		const auto CardBack = Cast<UCardBackInHand>(CardItem);
		CardBack->SetupCardBack(PlayerStatus.CardBack,PlayerStatus.ColorPalette,PlayerStatus.UseReserveColor);
	}
}
