// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStateEnums.h"
#include "DataFunctionLibrary.generated.h"

enum class ECardClass : uint8;
class UGoalkeepersPreset;
class UColorPreset;
class UCardBackPreset;
class UUniformPreset;
class UEmblemPreset;
class UDeckPreset;
class UUserPreset;
class UCardPreset;

UCLASS()
class DATA_API UDataFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UCardPreset*> LoadAllCards();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UUserPreset*> LoadAllUserPresets();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UDeckPreset*> LoadAllDecks();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UEmblemPreset*> LoadAllEmblems();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UUniformPreset*> LoadAllUniforms();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UCardBackPreset*> LoadAllCardBacks();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UColorPreset*> LoadAllColorPalettes();

	UFUNCTION(BlueprintCallable, Category = LoadLibrary)
	static TArray<UGoalkeepersPreset*> LoadAllGoalkeepers(const ECardClass CardClass = ECardClass::None);
};
