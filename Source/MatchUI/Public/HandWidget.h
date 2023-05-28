// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardDragDropOperation.h"
#include "HandWidgetBase.h"
#include "HandWidget.generated.h"

class AUnitActor;
class UDropAreaWidget;
class UNotificationContainer;
/**
 * 
 */
UCLASS()
class MATCHUI_API UHandWidget : public UHandWidgetBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Default)
	TSubclassOf<UCardInHandWidget> CardInHandClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UDropAreaWidget* DropArea;

	UFUNCTION(BlueprintCallable)
	void UseCard(UCard* Card);

	virtual void SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller) override;

	virtual void SetStatus(FPlayerStatus NewPlayerStatus) override;

protected:

	UPROPERTY(BlueprintReadWrite)
	bool DraggingCard;

	UPROPERTY(BlueprintReadWrite)
	AUnitActor* SelectedUnit;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DisableDropAreaTimerHandle;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	TSubclassOf<UNotificationContainer> MessageClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	FText NotEnoughManaMessage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	FText AlreadyHaveTrapCardMessage;

	UPROPERTY(BlueprintReadWrite)
	ETurnMoveState LastInteractionActive = ETurnMoveState::None;

	UFUNCTION(BlueprintCallable)
	void ActiveCardInteraction(UCardInHandWidget* Card);

	UFUNCTION(BlueprintCallable)
	void ManaChanged(int Amount);

	UFUNCTION(BlueprintCallable)
	void UpdateActiveCards();

	UFUNCTION(BlueprintCallable)
	void DisableDropArea();

	UFUNCTION(BlueprintCallable)
	void OnTryInteractWithCard(UCardInHandWidget* CardInHandWidget);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card) override;

	virtual TSubclassOf<UCardInHandWidgetBase> GetCardClass() override;
	void UnhoverUnit();
	void HoverUnit(const UCardDragDropOperation* CardOperation);
	void UpdateDragState();
};
