// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStateEnums.h"
#include "CardGameStructs.generated.h"

class UCardAbilityPreset;
class UCardTarget;

USTRUCT(BlueprintType)
struct FCard_System_Data
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ECardPurpose> cardPurpose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPlayConditions> playConditions;
};

USTRUCT(BlueprintType)
struct FCard_Level
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Mana Cost")
	int ManaCost = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Points")
	int Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine="true"))
	FText CardDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Abilities")
	TArray<UCardAbilityPreset*> AbilityPresets;
};





