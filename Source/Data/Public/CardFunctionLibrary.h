// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CardFunctionLibrary.generated.h"
class UCardPreset;
/**
 * 
 */
UCLASS()
class DATA_API UCardFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category= Deck)
	static bool IsUnitCard(UCardPreset* Card);

	UFUNCTION(BlueprintCallable, Category= Board)
	static int GetPointsByLevel(UCardPreset* Preset, int Level);
};
