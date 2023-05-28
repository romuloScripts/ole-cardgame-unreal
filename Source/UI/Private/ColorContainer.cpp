// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorContainer.h"
#include "Blueprint/WidgetTree.h"

void UColorContainer::NativePreConstruct()
{
	UpdateColor(ColorPreset);
	Super::NativePreConstruct();
}

void UColorContainer::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	OnUpdateColor(NewColorPreset);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (const auto Item : WidgetsArray)
	{
		UColorContainer* ColorContainer = Cast<UColorContainer>(Item);
		if (ColorContainer != nullptr)
		{
			ColorContainer->UseReserveColor = UseReserveColor;
			ColorContainer->UpdateColor(NewColorPreset);
		}
	}
}

void UColorContainer::UpdateColorAndReserve(UColorPreset* NewColorPreset, bool Reserve)
{
	UseReserveColor = Reserve;
	UpdateColor(NewColorPreset);
}

void UColorContainer::OnUpdateColor_Implementation(UColorPreset* NewColorPreset)
{
}
