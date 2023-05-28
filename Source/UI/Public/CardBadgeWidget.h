// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardCounterWidget.h"
#include "Components/Image.h"
#include "UObject/Object.h"
#include "CardBadgeWidget.generated.h"

class UIconsPreset;

UCLASS()
class UI_API UCardBadgeWidget : public UCardCounterWidget
{
	GENERATED_BODY()

public:
	
	virtual void UpdateCard(UCardPreset* NewCardPreset, int CardLevel) override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	UIconsPreset* IconsPreset;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Bg;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Outline;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Bg_Color1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Bg_Color2;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Bg_ColorBW;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* ManaCostBG;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* ManaCost_Text;
};
