// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AfterUseStateBase.h"
#include "AfterUseState.generated.h"

class UCardAbility;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,Abstract, EditInlineNew)
class CARDSYSTEM_API UAfterUseState : public UAfterUseStateBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void Setup(UCardAbility* CardAbility);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RemoveAfterUseState();

protected:

	UPROPERTY(BlueprintReadWrite)
	UCardAbility* Ability;

	UPROPERTY(BlueprintReadWrite)
	bool AbilityWasUsed;

	UFUNCTION(BlueprintCallable)
	void RemoveAbility() const;

	UFUNCTION(BlueprintCallable)
	void RemoveEffect();

	UFUNCTION(BlueprintCallable)
	void Used();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AbilityUsed();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void PostSetup();
};
