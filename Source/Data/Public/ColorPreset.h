// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ColorPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UColorPreset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName colorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer ColorTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ColorCard1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ColorCard2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ReserveColor1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ReserveColor2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ReserveColorCard1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ReserveColorCard2;

	UFUNCTION(BlueprintCallable)
    FLinearColor GetColor(bool SecondaryColor, bool ReserveColor, bool CardColor) const;

	UFUNCTION(BlueprintCallable)
	bool HasSameColorTag(UColorPreset* Other) const;
};
