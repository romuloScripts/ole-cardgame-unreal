// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardGameStructs.h"
#include "CardAbilityPreset.h"
#include "CardTargetBase.h"
#include "CardPreset.generated.h"

UCLASS(BlueprintType)
class DATA_API UCardPreset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Class")
	ECardClass CardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Type")
	ECardType CardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Rarity")
	ERarityType CardRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Mana Cost")
	int ManaCost = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Points",meta=(EditCondition="CardType != ECardType::Effect && CardType != ECardType::Trap",EditConditionHides))
	int Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartUnlockedInGame = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmountInDeck = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine="true"))
	FText CardDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine="true"))
	FText PlacementInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Instanced, meta=(EditCondition="CardType == ECardType::Effect || CardType == ECardType::Trap",EditConditionHides))
	UCardTargetBase* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCardAbilityPreset*> AbilityPresets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Levels Settings", meta=(EditCondition="CardType != ECardType::Effect && CardType != ECardType::Trap",EditConditionHides))
	TArray<FCard_Level> CardLevels;
};
