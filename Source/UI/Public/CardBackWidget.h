// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/Image.h"
#include "CardBackContainer.h"
#include "ColorContainer.h"
#include "CardBackWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UCardBackWidget : public UCardBackContainer
{
	GENERATED_BODY()
public:

	virtual void UpdateCardBack(UCardBackPreset* NewCardBack) override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* CardBackBW;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* CardBackColor1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* CardBackColor2;
};
