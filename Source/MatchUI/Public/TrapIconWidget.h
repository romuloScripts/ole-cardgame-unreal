// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "TrapIconWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool,FOnClickTrapIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveTrapIcon);

UCLASS()
class MATCHUI_API UTrapIconWidget : public UColorContainer
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FOnClickTrapIcon OnClickTrapIcon;
	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void AddTrap();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void RemoveTrap();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void ActivateTrap();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
