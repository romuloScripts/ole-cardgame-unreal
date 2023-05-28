// Fill out your copyright notice in the Description page of Project Settings.


#include "MulliganWidget.h"

#include "MatchPlayerState.h"
#include "MulliganCardWidget.h"
#include "WidgetFunctionLibrary.h"
#include "CardSystem/Public/Card.h"

void UMulliganWidget::NativePreConstruct()
{
	SetCards(CardsEditor);
	UpdateColor(User.ColorPalette);
	Super::NativePreConstruct();
}

void UMulliganWidget::SetCards(TArray<FCardWithLevel> Cards)
{
	CardsPanel->ClearChildren();
	CardsInstances.Empty();
	for(auto Card : Cards)
	{
		AddCard(Card);
	}
}

void UMulliganWidget::AddCard(const FCardWithLevel& CardWithLevel)
{
	if(!CardClass|| CardWithLevel.CardPreset == nullptr) return;
	const auto CardWidget = Cast<UMulliganCardWidget>(
		UWidgetFunctionLibrary::CreateCardInHorizontalBox(CardWithLevel.CardPreset,CardWithLevel.Level,
			CardClass,CardsPanel,User.Uniform,User.ColorPalette,User.UseReserveColor,CardsMargin));
	if(CardWidget)
		CardsInstances.Add(CardWidget);
}

void UMulliganWidget::SetUser(AMatchPlayerController* PlayerController, AMatchPlayerState* PlayerState)
{
	OwnerPlayerController = PlayerController;
	User = PlayerState->PlayerStatus;
	UpdateColorAndReserve(User.ColorPalette,User.UseReserveColor);
}

void UMulliganWidget::GetReplaceCards(TArray<int>& Cards)
{
	Cards.Empty();
	for(int i =0; i < CardsInstances.Num();i++)
	{
		auto Card = CardsInstances[i];
		if(Card->Selected)
		{
			Cards.Add(i);
		}
	}
}
