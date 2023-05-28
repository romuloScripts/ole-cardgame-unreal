// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityEffectBase.h"
#include "AbilityEffect.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUse);

UCLASS(Blueprintable,BlueprintType,Abstract,EditInlineNew)
class CARDSYSTEM_API UAbilityEffect : public UAbilityEffectBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void Use(UObject* DropTarget,UObject* TriggerTarget);

	UFUNCTION(BlueprintCallable)
	void Remove();

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnUse OnUse;
	
protected:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ApplyEffect(UObject* DropTarget,UObject* TriggerTarget);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RemoveEffect(UObject* DropTarget,UObject* TriggerTarget);

	UFUNCTION()
	virtual void NativeApplyEffect(UObject* DropTarget,UObject* TriggerTarget);

	UPROPERTY(BlueprintReadWrite)
	UObject* DTarget;

	UPROPERTY(BlueprintReadWrite)
	UObject* TTarget;
};
