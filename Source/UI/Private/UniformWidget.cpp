// Fill out your copyright notice in the Description page of Project Settings.


#include "UniformWidget.h"
#include "ColorPreset.h"
#include "UniformPreset.h"

void UUniformWidget::UpdateUniform(UUniformPreset* NewUniform)
{
	if(NewUniform == nullptr) return;
	UniformPreset = NewUniform;
	UniformColor1->SetBrushFromTexture(NewUniform->TextureColor1);
	UniformColor2->SetBrushFromTexture(NewUniform->TextureColor2);
}

void UUniformWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	UniformColor1->SetColorAndOpacity(NewColorPreset->GetColor(false,UseReserveColor,false));
	UniformColor2->SetColorAndOpacity(NewColorPreset->GetColor(true,UseReserveColor,false));
}
