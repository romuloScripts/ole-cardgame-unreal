// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardWidget.h"
#include "Components/Button.h"
#include "CardContainer.h"
#include "CardCounterWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendCardPreset,UCardPreset*,Card);

UCLASS()
class UI_API UCardCounterWidget : public UCardContainer
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintNativeEvent)
    void UpdateAmount(int Amount);
	
	UFUNCTION()
    void Hovered();

	UFUNCTION()
    void RemoveCardPopUp();

	UFUNCTION()
    void Unhovered();

	UFUNCTION(BlueprintNativeEvent)
    void OnShowOutline(bool Show);

	UFUNCTION()
    void Clicked();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
    void DisplayCardAtMousePosition();
    
	UPROPERTY(BlueprintAssignable)
	FOnSendCardPreset OnClickToRemove;

	UPROPERTY(BlueprintAssignable)
	FOnSendCardPreset OnClickToAdd;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	TSubclassOf<UCardWidget> CardWidget;

	UPROPERTY(BlueprintReadWrite, Category=Default)
	bool ShowOutline;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCardWidget*> CardPopUps;

private:
	
	UPROPERTY()
	FTimerHandle TimeHandle;
};
