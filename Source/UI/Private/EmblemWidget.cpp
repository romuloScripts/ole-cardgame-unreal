// Fill out your copyright notice in the Description page of Project Settings.


#include "EmblemWidget.h"

#include "ColorPreset.h"
#include "EmblemPreset.h"

void UEmblemWidget::UpdateEmblem(UEmblemPreset* NewEmblemPreset)
{
	if(NewEmblemPreset == nullptr) return;
	EmblemPreset = NewEmblemPreset;
	EmblemBW->SetBrushFromTexture(NewEmblemPreset->textureBW);
	EmblemColor2->SetBrushFromTexture(NewEmblemPreset->texturecolor2);
}

void UEmblemWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	EmblemColor1->SetColorAndOpacity(NewColorPreset->Color1);
	EmblemColor2->SetColorAndOpacity(NewColorPreset->Color2);
}
