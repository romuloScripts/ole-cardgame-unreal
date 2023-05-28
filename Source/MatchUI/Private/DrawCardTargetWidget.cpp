// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawCardTargetWidget.h"
#include "BoardFunctionLibrary.h"
#include "MatchPlayerState.h"
#include "WidgetFunctionLibrary.h"
#include "MulliganCardWidget.h"
#include "CardSelectTarget.h"
#include "UnitActor.h"

void UDrawCardTargetWidget::Setup(AMatchPlayerState* Player,UCardSelectTarget* CardSelectTarget)
{
	User = Player->PlayerStatus;
	UpdateColor(User.ColorPalette);
	Super::Setup(Player,CardSelectTarget);
	const auto Selections = CardSelectTarget->GetSelectionCandidates();
	TArray<FCardWithLevel> Cards;
	for(const auto Selection : Selections)
	{
		if(const auto Card = Cast<UCard>(Selection))
		{
			const auto Unit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Card->GetOwnerPlayer());
			FCardWithLevel CardWithLevel;
			CardWithLevel.Card = Card;
			CardWithLevel.CardPreset = Card->GetPreset();
			CardWithLevel.Level = Unit ? Unit->Level : 0;
			Cards.Add(CardWithLevel);
		}
	}
	SetCards(Cards);
}

void UDrawCardTargetWidget::NativePreConstruct()
{
	if(!IsDesignTime())
	{
		CardsEditor.Empty();
	}
	SetCards(CardsEditor);
	UpdateColor(User.ColorPalette);
	Super::NativePreConstruct();
}

void UDrawCardTargetWidget::SetCards(TArray<FCardWithLevel> Cards)
{
	CardsPanel->ClearChildren();
	CardsInstances.Empty();
	CardsMap.Empty();
	for(const auto Card : Cards)
	{
		AddCard(Card);
	}
}

void UDrawCardTargetWidget::AddCard(const FCardWithLevel& CardWithLevel)
{
	if(!CardClass|| CardWithLevel.CardPreset == nullptr) return;
	const auto CardContainer = UWidgetFunctionLibrary::CreateCardInHorizontalBox(CardWithLevel.CardPreset,CardWithLevel.Level,CardClass,CardsPanel,User.Uniform,User.ColorPalette,User.UseReserveColor,CardsMargin);
	if(const auto CardWidget = Cast<UMulliganCardWidget>(CardContainer))
	{
		CardsInstances.Add(CardWidget);
		if(!IsDesignTime() && CardWithLevel.Card)
		{
			CardsMap.Add(CardWidget,CardWithLevel.Card);
			CardWidget->OnCardClicked.AddDynamic(this,&UDrawCardTargetWidget::CardSelected);
		}
	}
}

void UDrawCardTargetWidget::CardSelected(UMulliganCardWidget* CardContainer)
{
	if(!CardsMap.Contains(CardContainer)) return;
	const auto Card = CardsMap[CardContainer];
	if(CardContainer->Selected)
	{
		PlayerState->ReceiveCardTargetSelection(Card);
	}else
	{
		PlayerState->RemoveCardTargetSelection(Card);
	}
}
