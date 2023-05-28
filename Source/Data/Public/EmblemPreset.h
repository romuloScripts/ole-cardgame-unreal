// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EmblemPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UEmblemPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName emblemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* textureBW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* texturecolor2;
	
};
