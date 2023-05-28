// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizationContainer.h"

#include "ColorContainer.h"
#include "Blueprint/WidgetTree.h"

void UCustomizationContainer::NativeConstruct()
{
	Super::NativeConstruct();   
	SelectionController = NewObject<USelectionController>();
	SelectionController->InitSelectablePanel(SelectablesContainer);
	UpdateSelected();

	for (UObject* Selectable : SelectionController->Selectables)
	{
		if(Selectable->Implements<USelectable>())
		{
			ISelectable::Execute_GetSelectEvent(Selectable)->OnClicked.AddDynamic(this,&UCustomizationContainer::OnClickedOption);
		}
	}
}

void UCustomizationContainer::OnUpdateContent_Implementation()
{
	UpdateSelected();
	if(!UpdateColor) return;
	for(UWidget* Widget: SelectablesContainer->GetAllChildren())
	{
		UColorContainer* ColorContainer = Cast<UColorContainer>(Widget);
		const auto Palette = Customization.ColorPalette;
		if(ColorContainer && Palette)
		{
			ColorContainer->UpdateColor(Palette);
		}
	}
}

void UCustomizationContainer::OnClickedOption_Implementation(UObject* Selected)
{
}

void UCustomizationContainer::UpdateSelected_Implementation()
{
}
