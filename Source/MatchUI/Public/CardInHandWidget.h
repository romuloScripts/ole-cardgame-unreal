// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardInHandWidgetBase.h"
#include "CardInHandWidget.generated.h"

class UCardWidget;
class AUnitActor;
class UCard;
class UColorPreset;
class UUniformPreset;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTryInteract, UCardInHandWidget*, CardInHand);

UCLASS()
class MATCHUI_API UCardInHandWidget : public UCardInHandWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardWidget* CardWidget;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnTryInteract FOnTryInteract;
	
	UFUNCTION(BlueprintCallable)
	void ActiveInteraction(const bool Active);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	void SetupCard(UCard* Card, UUniformPreset* Uniform, UColorPreset* Color,bool UseReserve);

	UFUNCTION(BlueprintCallable)
	int32 GetCardId() const;
	
	UFUNCTION(BlueprintCallable)
	UCard* GetCardData() const;

protected:

	UPROPERTY(BlueprintReadOnly)
	UCard* CardData;

	UPROPERTY(BlueprintReadOnly)
	AUnitActor* TargetUnit;

	UPROPERTY(BlueprintReadWrite)
	bool InteractionActivated;

	UFUNCTION(BlueprintCallable)
	void ActiveOutline(bool Active) const;

	UFUNCTION(BlueprintCallable)
	void OnLevelUp(int NewLevel);

	virtual void NativeDestruct() override;
};
