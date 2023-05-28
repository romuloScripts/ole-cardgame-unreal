// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UserStatusStructs.h"
#include "CardPlayedWidgetBase.generated.h"

class URichTextBlock;
class UCardWidget;
class UCardBackContainer;
class AMatchPlayerState;
/**
 * 
 */
UCLASS(Abstract)
class MATCHUI_API UCardPlayedWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	FPlayerStatus UserStatus;

	UFUNCTION(BlueprintCallable)
	virtual void SetUser(AMatchPlayerState* Player, bool IsOpponent);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void PostSetUser();
	
	virtual void NativePreConstruct() override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* GradientBG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UCardBackContainer* CardBack;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardWidget* Card;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* Description;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateVisual();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void PostUpdateVisual();
};
