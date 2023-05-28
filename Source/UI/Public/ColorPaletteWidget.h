// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/Image.h"
#include "ColorContainer.h"
#include "ColorPaletteWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UColorPaletteWidget : public UColorContainer
{
	GENERATED_BODY()
public:

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* ColorPaletteColor1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* ColorPaletteColor2;
};
