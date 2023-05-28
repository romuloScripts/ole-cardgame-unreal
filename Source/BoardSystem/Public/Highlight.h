// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Highlight.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHighlight : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOARDSYSTEM_API IHighlight
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Hover();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Unhover();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Active(const bool Value);
};
