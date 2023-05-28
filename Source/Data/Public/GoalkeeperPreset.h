// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardGameStructs.h"
#include "GoalkeeperPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UGoalkeepersPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName goalkeeperName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Class")
	ECardClass goalkeeperClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureColor1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureColor2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureShadow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* textureOutline;
	
};
