// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitContainer.h"
#include "CardContainer.generated.h"

class UCardPreset;
class UUniformPreset;
class UColorPreset;

UCLASS()
class UI_API UCardContainer : public UUnitContainer
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
    virtual void UpdateAllPResets(UCardPreset* NewCardPreset, int CardLevel, UUniformPreset* NewUniform, UColorPreset* NewColorPreset,bool ReserveColor);
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateCard(UCardPreset* NewCardPreset, int CardLevel);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateCard(UCardPreset* NewCardPreset, int num);

	UFUNCTION(BlueprintNativeEvent)
    void OnPostUpdateCard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	int level;
};
