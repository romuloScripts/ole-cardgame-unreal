// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBackContainer.h"

#include "Blueprint/WidgetTree.h"

void UCardBackContainer::NativePreConstruct()
{
	UpdateCardBack(CardBackPreset);
	Super::NativePreConstruct();
}

void UCardBackContainer::UpdateCardBack(UCardBackPreset* NewCardBack)
{
	if(NewCardBack == nullptr) return;
	CardBackPreset = NewCardBack;
	OnUpdateCardBack(NewCardBack);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (const auto Item : WidgetsArray)
	{
		UCardBackContainer* container = Cast<UCardBackContainer>(Item);
		if (container != nullptr)
		{
			container->UpdateCardBack(NewCardBack);
		}
	}
}

void UCardBackContainer::OnUpdateCardBack_Implementation(UCardBackPreset* NewCardBack)
{
}
