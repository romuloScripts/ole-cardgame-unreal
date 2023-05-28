// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTabs.h"

#include "WidgetFunctionLibrary.h"

void UMenuTabs::NativeConstruct()
{
	MenuSwitcherParams = UWidgetFunctionLibrary::BindButtonsWithSwitcher(TabsContainer,MenuWidgetSwitcher);
	MenuWidgetSwitcher->SetActiveWidgetIndex(0);
	
	SelectionController = NewObject<USelectionController>();
	SelectionController->InitSelectablePanel(TabsContainer);
	SelectionController->SelectAtIndex(0);
}
