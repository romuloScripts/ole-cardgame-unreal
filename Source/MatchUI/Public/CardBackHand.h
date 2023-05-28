// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandWidgetBase.h"
#include "CardBackHand.generated.h"

class UCardBackInHand;
/**
 * 
 */
UCLASS()
class MATCHUI_API UCardBackHand : public UHandWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Default)
	TSubclassOf<UCardBackInHand> CardInHandClass;
	
protected:

	virtual void SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card) override;

	virtual TSubclassOf<UCardInHandWidgetBase> GetCardClass() override;

	virtual void SetStatus(FPlayerStatus NewPlayerStatus) override;
};
