// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StatsPreset.generated.h"

USTRUCT(BlueprintType)
struct FStatSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(MultiLine=true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconBlack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconWhite;
};


UCLASS(Blueprintable,Blueprintable)
class DATA_API UStatsPreset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (Categories = "Stat"),meta=(TitleProperty="Name"))
	TMap<FGameplayTag,FStatSettings> Stats;
};


