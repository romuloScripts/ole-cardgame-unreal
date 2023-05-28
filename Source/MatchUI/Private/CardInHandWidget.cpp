// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHandWidget.h"
#include "BoardFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Card.h"
#include "CardWidget.h"
#include "UnitActor.h"

void UCardInHandWidget::ActiveInteraction(const bool Active)
{
	if(Active == InteractionActivated) return;
	InteractionActivated = Active;
	ActiveOutline(InteractionActivated);
}

void UCardInHandWidget::ActiveOutline(bool Active) const
{
	CardWidget->ActiveOutline(Active);
}

void UCardInHandWidget::OnLevelUp(int NewLevel)
{
	const int NextLevel = UBoardFunctionLibrary::GetUnitNextLevel(TargetUnit);
	CardWidget->UpdateCard(CardWidget->CardPreset,NextLevel);
}

void UCardInHandWidget::NativeDestruct()
{
	if(TargetUnit) TargetUnit->OnLevelUp.AddDynamic(this,&ThisClass::OnLevelUp);
	Super::NativeDestruct();
}

FReply UCardInHandWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InteractionActivated)
	{
		auto Result = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton);
		return Result.NativeReply.IsEventHandled() ? Result.NativeReply : Super::NativeOnMouseButtonDown(InGeometry,InMouseEvent);
	}
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) FOnTryInteract.Broadcast(this);
	return Super::NativeOnMouseButtonDown(InGeometry,InMouseEvent);
}

void UCardInHandWidget::SetupCard(UCard* Card, UUniformPreset* Uniform, UColorPreset* Color,bool UseReserve)
{
	CardData = Card;
	int NewLevel = 0;
	TargetUnit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Card->GetOwnerPlayer());
	if(TargetUnit)
	{
		NewLevel = UBoardFunctionLibrary::GetUnitNextLevel(TargetUnit);
		TargetUnit->OnLevelUp.AddDynamic(this,&ThisClass::OnLevelUp);
	}
	CardWidget->UpdateAllPResets(Card->GetPreset(),NewLevel,Uniform,Color,UseReserve);
}

int32 UCardInHandWidget::GetCardId() const
{
	return CardData->GetUniqueID();
}

UCard* UCardInHandWidget::GetCardData() const
{
	return CardData;
}

