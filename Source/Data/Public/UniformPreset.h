// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UniformPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UUniformPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UniformName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureColor1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureColor2;

};
