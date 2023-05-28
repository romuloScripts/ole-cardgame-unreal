// Fill out your copyright notice in the Description page of Project Settings.


#include "CardMenuItemWidget.h"
#include "DeckStructs.h"
#include "CardPreset.h"

void UCardMenuItemWidget::SetAmountAndMax(int Unlocked, int Used)
{
	LockImageVisibility(Unlocked);
	if(!CardPreset) return;
	AmountContainer->ClearChildren();

	if(!MarkerUsed || !MarkerFull || !MarkerEmpty) return;

	TSubclassOf<UUserWidget> Marker;

	for(int i =0;i<CardPreset->MaxAmountInDeck;i++)
	{
		if(i < Unlocked)
		{
			Marker = i < Used? MarkerUsed:MarkerFull;
		}
		else
		{
			Marker = MarkerEmpty;
		}
		const auto HorizontalSlot = AmountContainer->AddChild(CreateWidget<UUserWidget>(this,Marker));
		const FMargin Margin(2.0,0,2.0,0);
		Cast<UHorizontalBoxSlot>(HorizontalSlot)->SetPadding(Margin);
	}
}

void UCardMenuItemWidget::HideAmount()
{
	AmountContainer->SetVisibility(ESlateVisibility::Hidden);
}

void UCardMenuItemWidget::LockImageVisibility(int Amount)
{
	BP_Card->LockedImage->SetVisibility(Amount<=0?ESlateVisibility::Visible:ESlateVisibility::Hidden);
}

void UCardMenuItemWidget::NativeConstruct()
{
	CardItemButton->OnHovered.AddDynamic(this,&UCardMenuItemWidget::Hovered);
	CardItemButton->OnUnhovered.AddDynamic(this,&UCardMenuItemWidget::Unhovered);
	CardItemButton->OnClicked.AddDynamic(this,&UCardMenuItemWidget::OnClicked);
}

void UCardMenuItemWidget::Hovered()
{
	BP_Card->Outline->SetVisibility(ESlateVisibility::HitTestInvisible);
	StopAllAnimations();
	PlayAnimation(HoverIn_Anim);
}

void UCardMenuItemWidget::Unhovered()
{
	BP_Card->Outline->SetVisibility(ESlateVisibility::Hidden);
	StopAllAnimations();
	PlayAnimation(HoverOut_Anim);
}

void UCardMenuItemWidget::OnClicked()
{
	OnClickedEventCardItemMenu.Broadcast(this);
}

void UCardMenuItemWidget::PlayFeedbackAnimation(const EAddCardDeniedType AddCardDeniedType)
{
	if(AddCardDeniedType == EAddCardDeniedType::None)
		PlayAnimation(AddToDeck_Anim);
	else
		PlayAnimation(Deny_Anim);
}


