// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "TurnButtonWidget.generated.h"

class UButton;
class AMatchGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedTurnButton);


UCLASS()
class MATCHUI_API UTurnButtonWidget : public UColorContainer
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UpdateTime(float Time, float Duration);

	UFUNCTION()
	void OnClick();

	UFUNCTION(BlueprintCallable)
	void ActiveButton(const ESlateVisibility ESlateVisibility) const;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnClickedTurnButton OnClicked;

	UPROPERTY()
	AMatchGameState* GameState;
};
