// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilityEffect.h"
#include "AddStatEffect.generated.h"

/**
 * 
 */
UCLASS()
class CARDSYSTEM_API UAddStatEffect : public UAbilityEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default,meta = (Categories = "Stat"))
	FGameplayTag NewStat;
protected:
	void virtual NativeApplyEffect(UObject* DropTarget, UObject* TriggerTarget) override;
};
