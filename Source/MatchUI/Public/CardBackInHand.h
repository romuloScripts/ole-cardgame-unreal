// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardInHandWidgetBase.h"
#include "CardBackInHand.generated.h"

class UColorPreset;
class UCardBackPreset;
class UCardBackWidget;
/**
 * 
 */
UCLASS()
class MATCHUI_API UCardBackInHand : public UCardInHandWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardBackWidget* CardBack;
	
	UFUNCTION(BlueprintCallable)
	void SetupCardBack(UCardBackPreset* Preset, UColorPreset* Color, bool UseReserveColor);
};
