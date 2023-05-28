// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UniformContainer.h"
#include "UnitContainer.generated.h"

class UCardPreset;
/**
 * 
 */
UCLASS()
class UI_API UUnitContainer : public UUniformContainer
{
	GENERATED_BODY()
	
public:

	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateUnit(UCardPreset* NewUnit);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateUnit(UCardPreset* NewUnit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCardPreset* CardPreset;
};
