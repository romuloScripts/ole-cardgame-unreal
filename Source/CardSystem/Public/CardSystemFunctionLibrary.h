// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CardSystemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CARDSYSTEM_API UCardSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Card)
	static TArray<UCardAbilityPreset*> GetAbilityByLevel(UCardPreset* Preset, int Level);

	UFUNCTION(BlueprintCallable, Category = Card)
	static UCardAbility* CreateAbility(const FCardDropTargetInfo& DropInfo, UCardAbilityPreset* CardAbilityPreset, UCard* Card = nullptr);
};
