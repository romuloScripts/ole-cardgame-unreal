// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YellowCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATCHUI_API UYellowCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void AddYellowCard();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void RemoveYellowCard();
};
