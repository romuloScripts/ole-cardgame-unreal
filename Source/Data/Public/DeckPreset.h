// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeckStructs.h"


#include "DeckPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UDeckPreset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FDeck Deck;
};
