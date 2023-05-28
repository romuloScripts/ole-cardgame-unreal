// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalkeeperContainer.h"

#include "Blueprint/WidgetTree.h"

void UGoalkeeperContainer::NativePreConstruct()
{
	UpdateGoalkeeper(GoalkeepersPreset);
	Super::NativePreConstruct();
}

void UGoalkeeperContainer::UpdateGoalkeeper(UGoalkeepersPreset* NewGoalkeepersPreset)
{
	if(NewGoalkeepersPreset == nullptr) return;
	GoalkeepersPreset = NewGoalkeepersPreset;
	OnUpdateGoalkeeper(NewGoalkeepersPreset);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (auto Item : WidgetsArray)
	{
		UGoalkeeperContainer* Goalkeeper = Cast<UGoalkeeperContainer>(Item);
		if (Goalkeeper != nullptr)
		{
			Goalkeeper->UpdateGoalkeeper(NewGoalkeepersPreset);
		}
	}
}

void UGoalkeeperContainer::OnUpdateGoalkeeper_Implementation(UGoalkeepersPreset* NewGoalkeepersPreset)
{
}
