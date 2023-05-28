// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "UnitContainer.h"
#include "UnitWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnClickUnit);

UCLASS()
class UI_API UUnitWidget : public UUnitContainer
{
	GENERATED_BODY()

public:

	virtual auto UpdateUnit(UCardPreset* NewUnit) -> void override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Unit;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Unit_Outline;

	UPROPERTY()
	FOnClickUnit OnRightClick;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
