// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPaletteWidget.h"
#include "ColorPreset.h"

void UColorPaletteWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	ColorPaletteColor1->SetColorAndOpacity(NewColorPreset->Color1);
	ColorPaletteColor2->SetColorAndOpacity(NewColorPreset->Color2);
}
