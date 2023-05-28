// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionScreenWidget.h"

#include "ActionInfoWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UActionScreenWidget::ShowActionInfo(FVector WorldPos, int Cost, const FText& Action, const bool Blocked)
{
	const auto Player = GetOwningPlayer();
	FVector2D Pos2D;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Player,WorldPos,Pos2D,false);
	ActionInfo->SetVisibility(ESlateVisibility::HitTestInvisible);
	const auto CanvasSlot = Cast<UCanvasPanelSlot>(ActionInfo->Slot);
	CanvasSlot->SetPosition(Pos2D);
	ActionInfo->SetAction(Cost,Action,Blocked);
}

void UActionScreenWidget::HideActionInfo() const
{
	if(ActionInfo->GetVisibility() != ESlateVisibility::Hidden)
	{
		ActionInfo->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UActionScreenWidget::IsHidden() const
{
	return ActionInfo->GetVisibility() == ESlateVisibility::Hidden;
}
