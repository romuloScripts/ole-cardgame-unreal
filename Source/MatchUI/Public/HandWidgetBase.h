// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatusContainer.h"
#include "HandWidgetBase.generated.h"

class UCardInHandWidgetBase;
class UCard;
class UCanvasPanel;
/**
 * 
 */
UCLASS(Abstract)
class MATCHUI_API UHandWidgetBase : public UPlayerStatusContainer
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Default)
	FVector2D CardsSize = FVector2D(200,320);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Default)
	FVector2D CardsDistance = FVector2D(180,80);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Default)
	float HandHeight = 110;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* HandCanvasPanel;

	UFUNCTION(BlueprintCallable)
	void AddCardsToHand(const TArray<UCard*>& NewCards);

	UFUNCTION(BlueprintCallable)
	void RemovedCardsToHand(const TArray<UCard*>& NewCards);

	virtual void SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller) override;

protected:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	bool PlayAnimWhenRemoveCard;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	float CardDrawDelay = 0.6f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	TArray<UCardPreset*> TestCards;

	UPROPERTY(BlueprintReadWrite)
	TMap<UCard*,UCardInHandWidgetBase*> Cards;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCardInHandWidgetBase*> CardsOrder;

	UPROPERTY(BlueprintReadWrite)
	float CardTimer;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCard*> CardDrawStack;

	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card);

	UFUNCTION(BlueprintCallable)
	virtual void AddCardToHand(UCard* Card);

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UCardInHandWidgetBase> GetCardClass();

	UFUNCTION(BlueprintCallable)
	void RemoveCard(UCard* CardToRemove);
	
	UFUNCTION(BlueprintCallable)
	void RemoveCardByPosition(const int Position);

	UFUNCTION(BlueprintCallable)
	void UpdateCardsPositions();
	
	UFUNCTION(BlueprintCallable)
	void OnEndRemove(UCardInHandWidgetBase* CardInHand);
	
	UFUNCTION(BlueprintCallable)
	void DrawCardTick(float InDeltaTime);

	UFUNCTION()
	void AddCardsWithoutDelay(const TArray<UCard*>& NewCards);

	UFUNCTION()
	void AddCardsWithDelay(const TArray<UCard*>& NewCards);
};
