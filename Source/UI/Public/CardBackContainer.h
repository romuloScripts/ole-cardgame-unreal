// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "CardBackPreset.h"

#include "CardBackContainer.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UCardBackContainer : public UColorContainer
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateCardBack(UCardBackPreset* NewCardBack);

	UFUNCTION(BlueprintNativeEvent)
	void OnUpdateCardBack(UCardBackPreset* NewCardBack);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCardBackPreset* CardBackPreset;
};
