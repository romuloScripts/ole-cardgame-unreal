// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBackWidget.h"

#include "ColorPreset.h"

void UCardBackWidget::UpdateCardBack(UCardBackPreset* NewCardBack)
{
	if(NewCardBack == nullptr) return;
	CardBackPreset = NewCardBack;
	CardBackBW->SetBrushFromTexture(NewCardBack->textureBW);
	CardBackColor2->SetBrushFromTexture(NewCardBack->texturecolor2);
}

void UCardBackWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	CardBackColor1->SetColorAndOpacity(NewColorPreset->GetColor(false,UseReserveColor,false));
	CardBackColor2->SetColorAndOpacity(NewColorPreset->GetColor(true,UseReserveColor,false));
}
