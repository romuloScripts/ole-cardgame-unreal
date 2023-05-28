// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardBackPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UCardBackPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName cardBackName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureBW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* texturecolor2;

};
