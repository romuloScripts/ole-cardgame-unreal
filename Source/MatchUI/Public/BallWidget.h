// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SetupBallActor.h"
#include "Blueprint/UserWidget.h"
#include "BallWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATCHUI_API UBallWidget : public UUserWidget, public ISetupBallActor
{
	GENERATED_BODY()
public:

	virtual void Setup_Implementation(ABallActor* BallActor) override;
	
	UFUNCTION(BlueprintCallable)
	void ActiveInteraction(bool Value);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void Hover();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void Unhover();

	UFUNCTION()
	void HoverEvent(bool Value);
};
