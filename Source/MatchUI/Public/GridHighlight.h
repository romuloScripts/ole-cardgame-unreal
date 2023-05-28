// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Highlight.h"
#include "Blueprint/UserWidget.h"
#include "GridHighlight.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable,Abstract)
class MATCHUI_API UGridHighlight : public UUserWidget, public IHighlight
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	virtual void Hover_Implementation() override;
	
	virtual void Unhover_Implementation() override;
	
	virtual void Active_Implementation(const bool Value)override;

	UFUNCTION()
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_HoverIn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_HoverOut;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_HoverIdle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_Click;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_Idle;
};
