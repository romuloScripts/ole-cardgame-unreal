// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserStatusStructs.h"
#include "UObject/Object.h"
#include "CustomizationPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UCustomizationPreset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCustomizationData DefaultCustomization;
};
