// Fill out your copyright notice in the Description page of Project Settings.


#include "UniformContainer.h"
#include "Blueprint/WidgetTree.h"

void UUniformContainer::NativePreConstruct()
{
	UpdateUniform(UniformPreset);
	Super::NativePreConstruct();
}

void UUniformContainer::UpdateUniform(UUniformPreset* NewUniform)
{
	if(NewUniform == nullptr) return;
	UniformPreset = NewUniform;
	OnUpdateUniform(NewUniform);
	TArray<UWidget*> WidgetsArray;
	this->WidgetTree->GetAllWidgets(WidgetsArray);
	for (auto Item : WidgetsArray)
	{
		UUniformContainer* UniformWidget = Cast<UUniformContainer>(Item);
		if (UniformWidget != nullptr)
		{
			UniformWidget->UpdateUniform(NewUniform);
		}
	}
}

void UUniformContainer::OnUpdateUniform_Implementation(UUniformPreset* NewUniform)
{
}
