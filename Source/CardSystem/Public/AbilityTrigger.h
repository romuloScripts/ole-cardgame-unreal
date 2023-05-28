// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityTriggerBase.h"
#include "AbilityTrigger.generated.h"

class UCardAbility;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,Abstract,EditInlineNew)
class CARDSYSTEM_API UAbilityTrigger : public UAbilityTriggerBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Setup(UCardAbility* CardAbility);

	UFUNCTION(BlueprintCallable)
	void Remove();

	UFUNCTION(BlueprintCallable)
	void Active();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxTriggers;

	UPROPERTY(BlueprintReadWrite)
	UCardAbility* Ability;

	UPROPERTY(BlueprintReadWrite)
	int TotalTriggers;

	UFUNCTION(BlueprintCallable)
	void TriggerAbility(UObject* TriggerTarget);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ObserveTriggerCondition();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RemoveObserveTriggerCondition();
};
