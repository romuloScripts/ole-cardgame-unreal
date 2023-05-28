// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalkeeperWidget.h"

#include "ColorPreset.h"
#include "GoalkeeperPreset.h"

void UGoalkeeperWidget::UpdateGoalkeeper(UGoalkeepersPreset* NewGoalkeepersPreset)
{
	if(NewGoalkeepersPreset == nullptr) return;
	GoalkeepersPreset = NewGoalkeepersPreset;
	Outline->SetBrushFromTexture(NewGoalkeepersPreset->textureOutline);
	Base->SetBrushFromTexture(NewGoalkeepersPreset->textureBase);
	Color1->SetBrushFromTexture(NewGoalkeepersPreset->textureColor1);
	Color2->SetBrushFromTexture(NewGoalkeepersPreset->textureColor2);
	Light->SetBrushFromTexture(NewGoalkeepersPreset->textureLight);
	Shadow->SetBrushFromTexture(NewGoalkeepersPreset->textureShadow);
}

void UGoalkeeperWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	if(UseReserveColor)
	{
		Color1->SetColorAndOpacity(NewColorPreset->ReserveColor1);
		Color2->SetColorAndOpacity(NewColorPreset->ReserveColor2);
	}
	else
	{
		Color1->SetColorAndOpacity(NewColorPreset->Color1);
		Color2->SetColorAndOpacity(NewColorPreset->Color2);
	}
}