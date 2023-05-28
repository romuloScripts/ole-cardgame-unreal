// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ColorContainer.generated.h"

class UColorPreset;

UCLASS()
class UI_API UColorContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
    virtual void UpdateColor(UColorPreset* NewColorPreset);

	UFUNCTION(BlueprintCallable)
    virtual void UpdateColorAndReserve(UColorPreset* NewColorPreset, bool Reserve);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateColor(UColorPreset* NewColorPreset);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UColorPreset* ColorPreset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool UseReserveColor;
};
