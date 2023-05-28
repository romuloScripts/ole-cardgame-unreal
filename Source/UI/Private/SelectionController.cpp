// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionController.h"
#include "Blueprint/WidgetTree.h"
#include "SelectParams.h"


void USelectionController::InitSelectablePanel(UPanelWidget* Panel)
{
	TArray<UObject*> SelectablesArray;
	for (auto Item : Panel->GetAllChildren())
	{
		if (Item->Implements<USelectable>())
		{
			SelectablesArray.Add(Item);
		}
	}
	if(SelectablesArray.Num()>0)
		InitSelectables(SelectablesArray);
}


void USelectionController::InitSelectableContainer(UUserWidget* SelectablesContainer)
{
	TArray<UWidget*> WidgetsArray;
	TArray<UObject*> SelectablesArray;
	SelectablesContainer->WidgetTree->GetAllWidgets(WidgetsArray);
	for (auto Item : WidgetsArray)
	{
		if (Item->Implements<USelectable>())
		{
			SelectablesArray.Add(Item);
		}
	}
	if(SelectablesArray.Num()>0)
		InitSelectables(SelectablesArray);
}

void USelectionController::InitSelectables(TArray<UObject*> SelectablesArray)
{
	Selectables = SelectablesArray;
	for (auto Selectable : Selectables)
	{
		USelectParams* SelectParams= NewObject<USelectParams>(this);
		SelectParams->Init(Selectable);
		SelectParams->OnSelectEvent.AddDynamic(this,&USelectionController::UnselectAllOthers);
		SelectParamsArray.Add(SelectParams);
	}
}

void USelectionController::UnselectAll()
{
	for (auto Selectable : Selectables)
	{
		if(ISelectable::Execute_IsSelectedState(Selectable))
		{
			ISelectable::Execute_Unselect(Selectable);
		}
	}
}

void USelectionController::Select(UObject* Select)
{
	ISelectable::Execute_Select(Select);
}

void USelectionController::SelectAtIndex(int index)
{
	ISelectable::Execute_Select(Selectables[index]);
}

void USelectionController::UnselectAllOthers(UObject* Selected)
{
	for (auto Selectable : Selectables)
	{
		if(ISelectable::Execute_IsSelectedState(Selectable) && Selectable != Selected)
		{
			ISelectable::Execute_Unselect(Selectable);
		}
	}
}
