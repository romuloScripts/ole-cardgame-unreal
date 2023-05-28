// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitWidget.h"
#include "CardFunctionLibrary.h"
#include "CardPreset.h"

void UUnitWidget::UpdateUnit(UCardPreset* NewUnit)
{
	if(NewUnit == nullptr || !UCardFunctionLibrary::IsUnitCard(NewUnit)) return;
	CardPreset = NewUnit;
	Unit->SetBrushFromTexture(NewUnit->Texture1);
	Unit_Outline->SetBrushFromTexture(NewUnit->Texture2);
}

FReply UUnitWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && OnRightClick.IsBound() && OnRightClick.Execute())
	{
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
