// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "StatIconWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MATCHUI_API UStatIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default,meta = (Categories = "Stat"))
	FGameplayTag Stat;
	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void AddIcon(FGameplayTag NewStat);
};
