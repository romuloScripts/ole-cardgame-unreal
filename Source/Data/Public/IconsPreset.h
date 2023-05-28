// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CardGameStructs.h"
#include "IconsPreset.generated.h"

USTRUCT(BlueprintType)
struct FTypeTextures
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FilterTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BgTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FrameTexture;
};

USTRUCT(BlueprintType)
struct FCardClassTextures
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FilterTexture;
};

USTRUCT(BlueprintType)
struct FRarityTextures
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FilterTexture;
};

USTRUCT(BlueprintType)
struct FLevelTextures
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CardTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UnitTexture;
};


UCLASS(BlueprintType)
class DATA_API UIconsPreset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	TMap<ECardType, FTypeTextures> TypeMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	TMap<ECardClass, FCardClassTextures> ClassMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	TMap<ERarityType, FRarityTextures> RarityMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	TMap<int32, FLevelTextures> LevelMap;
};
