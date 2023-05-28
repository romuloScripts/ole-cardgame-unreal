// Fill out your copyright notice in the Description page of Project Settings.


#include "CardContainer.h"

#include "Blueprint/WidgetTree.h"

void UCardContainer::NativePreConstruct()
{
	UpdateCard(CardPreset, level);
	Super::NativePreConstruct();
}

void UCardContainer::UpdateAllPResets(UCardPreset* NewCardPreset, int CardLevel, UUniformPreset* NewUniform,
	UColorPreset* NewColorPreset, bool ReserveColor)
{
	UpdateCard(NewCardPreset, CardLevel);
	UpdateUnit(NewCardPreset);
	UpdateUniform(NewUniform);
	UpdateColorAndReserve(NewColorPreset,ReserveColor);
}

void UCardContainer::UpdateCard(UCardPreset* NewCardPreset, int CardLevel)
{
	if(CardLevel < 0 || NewCardPreset == nullptr) return;
	CardPreset = NewCardPreset;
	level = CardLevel;
	OnUpdateCard(NewCardPreset, CardLevel);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (auto Item : WidgetsArray)
	{
		UCardContainer* UniformWidget = Cast<UCardContainer>(Item);
		if (UniformWidget != nullptr)
		{
			UniformWidget->UpdateCard(NewCardPreset, CardLevel);
		}
	}
	OnPostUpdateCard();
}

void UCardContainer::OnPostUpdateCard_Implementation()
{
}

void UCardContainer::OnUpdateCard_Implementation(UCardPreset* NewCardPreset, int num)
{
}
