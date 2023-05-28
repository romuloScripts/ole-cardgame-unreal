// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/Image.h"
#include "GoalkeeperContainer.h"
#include "GoalkeeperWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UGoalkeeperWidget : public UGoalkeeperContainer
{
	GENERATED_BODY()

public:

	virtual void UpdateGoalkeeper(UGoalkeepersPreset* NewGoalkeepersPreset) override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Outline;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Base;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Color1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Color2;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Light;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* Shadow;
};
