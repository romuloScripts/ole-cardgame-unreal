// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "SelectEvent.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UI_API ISelectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	USelectEvent* GetSelectEvent();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsSelectedState();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Unselect();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Select();
};
