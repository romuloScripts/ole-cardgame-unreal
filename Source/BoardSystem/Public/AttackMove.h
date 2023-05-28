
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnitMove.h"
#include "UObject/Object.h"
#include "AttackMove.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOARDSYSTEM_API UAttackMove : public UUnitMove
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	AUnitActor* OpponentUnit;
	
	FTimerHandle DelayAttackTimer;

	UFUNCTION()
	virtual void EndAttack();
	void Attack(AActor* Target, EMoveType MoveType, EDamageType DamageType, EMoveType MoveReceived);

	UFUNCTION()
	virtual void BeginAttack(AActor* Target,EMoveType MoveType,EDamageType DamageType,EMoveType MoveReceived);
	void DoubleAttack();
};
