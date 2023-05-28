// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ManaCellWidget.generated.h"

UENUM(BlueprintType)
enum class EManaCellState : uint8
{
	Full,
    Spent,
    Empty,
	WillSpend,
	ReturnNormalState
};

UCLASS()
class MATCHUI_API UManaCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpacitySpent = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Default)
	EManaCellState state;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* manaEmpty;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* manaBall;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Spend;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Jumping;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Idle;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Empty;

	UFUNCTION(BlueprintCallable)
	void UpdateState(EManaCellState NewState);
};
