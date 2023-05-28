// Fill out your copyright notice in the Description page of Project Settings.


#include "HandWidgetBase.h"

#include "CardInHandWidgetBase.h"
#include "MatchPlayerState.h"
#include "CardSystem/Public/Card.h"
#include "Components/CanvasPanel.h"

void UHandWidgetBase::AddCardsToHand(const TArray<UCard*>& NewCards)
{
	if(IsDesignTime())
	{
		AddCardsWithoutDelay(NewCards);
	}else
	{
		CardTimer = 0;
		for (int i = 0; i < NewCards.Num();i++)
		{
			CardDrawStack.Add(NewCards[i]);
		}
	}
}

void UHandWidgetBase::RemovedCardsToHand(const TArray<UCard*>& NewCards)
{
	for(const auto Card: NewCards)
	{
		RemoveCard(Card);
	}
}

void UHandWidgetBase::SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller)
{
	Super::SetUser(State, Controller);
	PlayerState->OnAddCardInHand.AddDynamic(this,&UHandWidgetBase::AddCardsToHand);
	PlayerState->OnRemovedCardInHand.AddDynamic(this,&UHandWidgetBase::RemovedCardsToHand);
}

void UHandWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	for (const auto Card : Cards)
	{
		Card.Value->RemoveFromParent();
	}
	Cards.Empty();
	if(IsDesignTime())
	{
		TArray<UCard*> Array;
		for(const auto Preset : TestCards)
		{
			auto Card = NewObject<UCard>();
			Card->Setup(Preset,nullptr);
			Array.Add(Card);
		}
		AddCardsToHand(Array);
	}
}

void UHandWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	DrawCardTick(InDeltaTime);
}

void UHandWidgetBase::SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card)
{
}

void UHandWidgetBase::AddCardToHand(UCard* Card)
{
	if(Card == nullptr) return;
	const auto CardVisual = CreateWidget<UCardInHandWidgetBase>(this,GetCardClass());
	HandCanvasPanel->AddChild(CardVisual);
	CardVisual->SetSize(CardsSize);
	Cards.Add(Card,CardVisual);
	CardsOrder.Add(CardVisual);
	SetupCard(CardVisual,Card);
	if(!IsDesignTime())
	{
		CardVisual->PlayDrawCard();
		CardVisual->OnRemoveAnimEnd.AddDynamic(this,&UHandWidgetBase::OnEndRemove);
	}
}

TSubclassOf<UCardInHandWidgetBase> UHandWidgetBase::GetCardClass()
{
	return nullptr;
}

void UHandWidgetBase::RemoveCard(UCard* CardToRemove)
{
	if(!Cards.Contains(CardToRemove)) return;

	const auto CardWidget = Cards[CardToRemove];
	CardsOrder.Remove(CardWidget);
	Cards.Remove(CardToRemove);
	
	if(PlayAnimWhenRemoveCard)
	{
		CardWidget->PlayRemove();
	}else
	{
		OnEndRemove(CardWidget);
	}
}

void UHandWidgetBase::RemoveCardByPosition(const int Position)
{
	if(Position >= Cards.Num()) return;
	TArray<UCard*> Keys;
	Cards.GetKeys(Keys);
	UCard* Key = Keys[Position];
	RemoveCard(Key);
}

void UHandWidgetBase::UpdateCardsPositions()
{
	const int Amount = Cards.Num();
	const int Distance = FMath::TruncToInt(
		FMath::GetMappedRangeValueClamped(FVector2D(0,10),FVector2D(CardsDistance.X,CardsDistance.Y),Amount));
	for (int i =0; i < Amount;i++)
	{
		const auto Card = CardsOrder[i];
		Card->SetDefaultZOrder(i);
		const float X = i * Distance - (Distance * Amount) / 2.0f  + (Distance/2.0f);
		Card->SetCarPos(FVector2D(X,HandHeight));
	}
}

void UHandWidgetBase::OnEndRemove(UCardInHandWidgetBase* CardInHand)
{
	CardInHand->RemoveFromParent();
	UpdateCardsPositions();
}

void UHandWidgetBase::DrawCardTick(float InDeltaTime)
{
	if(CardDrawStack.Num()<=0) return;
	
	if(CardTimer > 0)
	{
		CardTimer -= InDeltaTime;
	}else
	{
		AddCardToHand(CardDrawStack[0]);
		CardDrawStack.RemoveAt(0);
		UpdateCardsPositions();
		CardTimer = CardDrawDelay;
	}
}

void UHandWidgetBase::AddCardsWithoutDelay(const TArray<UCard*>& NewCards)
{
	const int Amount = NewCards.Num();
	for (int i =0; i < Amount;i++)
	{
		AddCardToHand(NewCards[i]);
	}
	UpdateCardsPositions();
}

void UHandWidgetBase::AddCardsWithDelay(const TArray<UCard*>& NewCards)
{
	CardDrawStack.Append(NewCards);
}
