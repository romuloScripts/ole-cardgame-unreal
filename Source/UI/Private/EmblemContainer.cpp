// Fill out your copyright notice in the Description page of Project Settings.


#include "EmblemContainer.h"
#include "EmblemPreset.h"
#include "Blueprint/WidgetTree.h"

void UEmblemContainer::NativePreConstruct()
{
	UpdateEmblem(EmblemPreset);
	Super::NativePreConstruct();
}

void UEmblemContainer::UpdateEmblem(UEmblemPreset* NewEmblemPreset)
{
	if(NewEmblemPreset == nullptr) return;
	EmblemPreset = NewEmblemPreset;
	OnUpdateEmblem(NewEmblemPreset);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (const auto Item : WidgetsArray)
	{
		UEmblemContainer* Emblem = Cast<UEmblemContainer>(Item);
		if (Emblem != nullptr)
		{
			Emblem->UpdateEmblem(NewEmblemPreset);
		}
	}
}

void UEmblemContainer::OnUpdateEmblem_Implementation(UEmblemPreset* NewEmblemPreset)
{
}
