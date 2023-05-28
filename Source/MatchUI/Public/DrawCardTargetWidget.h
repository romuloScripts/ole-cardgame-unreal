// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTargetWidget.h"
#include "Components/HorizontalBox.h"
#include "UserStatusStructs.h"
#include "Card.h"
#include "DrawCardTargetWidget.generated.h"

class UMulliganCardWidget;
/**
 * 
 */
UCLASS(Abstract)
class MATCHUI_API UDrawCardTargetWidget : public UCardTargetWidget
{
	GENERATED_BODY()

public:
	virtual void Setup(AMatchPlayerState* Player,UCardSelectTarget* CardSelectTarget) override;
protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	FPlayerStatus User;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	TSubclassOf<UMulliganCardWidget> CardClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	FMargin CardsMargin = FMargin(12,0,12,0);

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UHorizontalBox* CardsPanel;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	TArray<FCardWithLevel> CardsEditor;

	UPROPERTY(BlueprintReadWrite, Category=Default)
	TArray<UMulliganCardWidget*> CardsInstances;

	UPROPERTY(BlueprintReadWrite, Category=Default)
	TMap<UMulliganCardWidget*,UCard*> CardsMap;

	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void SetCards(TArray<FCardWithLevel> Cards);

	UFUNCTION(BlueprintCallable)
	void AddCard(const FCardWithLevel& CardWithLevel);

	UFUNCTION(BlueprintCallable)
	void CardSelected(UMulliganCardWidget* CardContainer);
};
