// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardAbility.generated.h"

class UCardAbilityPreset;
class UCard;
class UAfterUseState;
class UAbilityTrigger;
class UAbilityContainer;
class UAbilityEffect;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class CARDSYSTEM_API UCardAbility : public UObject
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite,Category=Default)
	UAbilityContainer* OwnerContainer;
	
	UPROPERTY(BlueprintReadWrite,Category=Default)
	UAbilityEffect* Effect;
	
	UPROPERTY(BlueprintReadWrite,Category=Default)
	UAbilityTrigger* Trigger;

	UPROPERTY(BlueprintReadWrite,Category=Default)
	UAfterUseState* AfterUseState;

	UPROPERTY(BlueprintReadWrite,Category=Default)
	UObject* DropTarget;

	UPROPERTY(BlueprintReadWrite,Category=Default)
	UCard* OwnerCard;

	UFUNCTION(BlueprintCallable)
	void Setup(UAbilityContainer* Container, UObject* Target,const UCardAbilityPreset* CardAbilityPreset,UCard* Card = nullptr);

	UFUNCTION(BlueprintCallable)
	void Remove();
	
	UFUNCTION(BlueprintCallable)
	void TriggerAbility(UObject* TriggerTarget);

	UFUNCTION(BlueprintCallable)
	bool IsTrapAbility();
	
	UFUNCTION(BlueprintCallable)
	APlayerState* GetPlayerState() const;
};
