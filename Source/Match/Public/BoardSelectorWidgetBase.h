// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoardSelectorWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MATCH_API UBoardSelectorWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void ShowActionInfo(FVector WorldPos, int Cost, const FText& Action, bool Blocked);

	UFUNCTION()
	virtual void HideActionInfo() const PURE_VIRTUAL(UBoardSelectorWidgetBase::HideActionInfo, )

	UFUNCTION()
	virtual bool IsHidden() const PURE_VIRTUAL(UBoardSelectorWidgetBase::IsHidden, return false;);
};
