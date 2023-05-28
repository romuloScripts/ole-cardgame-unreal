// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "CardTargetWidget.generated.h"

class AMatchPlayerState;
class UCardSelectTarget;

UCLASS(Abstract)
class MATCHUI_API UCardTargetWidget : public UColorContainer
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void Setup(AMatchPlayerState* Player, UCardSelectTarget* CardSelectTarget);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ShowTargets();

protected:
	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;
};
