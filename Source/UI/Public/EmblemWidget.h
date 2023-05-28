// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/Image.h"
#include "EmblemContainer.h"
#include "UObject/Object.h"
#include "EmblemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UEmblemWidget : public UEmblemContainer
{
	GENERATED_BODY()

public:

	virtual void UpdateEmblem(UEmblemPreset* NewEmblemPreset) override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* EmblemBW;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* EmblemColor1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* EmblemColor2;
};
