// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackMove.h"
#include "UObject/Object.h"
#include "StealBallMove.generated.h"

/**
 * 
 */
UCLASS()
class BOARDSYSTEM_API UStealBallMove : public UAttackMove
{
	GENERATED_BODY()
protected:
	virtual void Move(AActor* Target) override;

	virtual bool TargetIsValid(AActor* Target) override;

	virtual void EndAttack() override;
};
