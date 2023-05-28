// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitContainer.h"

#include "Blueprint/WidgetTree.h"

void UUnitContainer::NativePreConstruct()
{
	UpdateUnit(CardPreset);
	Super::NativePreConstruct();
}

void UUnitContainer::UpdateUnit(UCardPreset* NewUnit)
{
	if(NewUnit == nullptr) return;
	CardPreset = NewUnit;
	OnUpdateUnit(NewUnit);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (const auto Item : WidgetsArray)
	{
		UUnitContainer* UniformWidget = Cast<UUnitContainer>(Item);
		if (UniformWidget != nullptr)
		{
			UniformWidget->UpdateUnit(NewUnit);
		}
	}
}

void UUnitContainer::OnUpdateUnit_Implementation(UCardPreset* NewUnit)
{
}
