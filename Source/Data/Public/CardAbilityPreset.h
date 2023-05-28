// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTriggerBase.h"
#include "AbilityEffectBase.h"
#include "AfterUseStateBase.h"
#include "CardAbilityPreset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DATA_API UCardAbilityPreset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UAbilityEffectBase* Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UAbilityTriggerBase* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UAfterUseStateBase* AfterUseState;
};
