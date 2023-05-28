// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomizationPreset.h"
#include "DeckPreset.h"
#include "UserStatusStructs.h"
#include "UObject/Object.h"
#include "UserPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UUserPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUserStatus UserStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCustomizationPreset* DefaultCustomization;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeckPreset*> Decks;
};
