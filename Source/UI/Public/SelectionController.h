// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Selectable.h"
#include "UObject/Object.h"
#include "SelectionController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UI_API USelectionController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InitSelectablePanel(UPanelWidget* Panel);
	
	UFUNCTION(BlueprintCallable)
	void InitSelectableContainer(UUserWidget* SelectablesContainer);

	UFUNCTION(BlueprintCallable)
	void InitSelectables(TArray<UObject*> SelectablesArray);
	
	UFUNCTION(BlueprintCallable)
	void UnselectAll();

	UFUNCTION(BlueprintCallable)
	void Select(UObject* Select);

	UFUNCTION(BlueprintCallable)
	void SelectAtIndex(int index);

	UFUNCTION(BlueprintCallable)
    void UnselectAllOthers(UObject* Selected);

	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> Selectables;

	UPROPERTY()
	TArray<UObject*> SelectParamsArray;
};
