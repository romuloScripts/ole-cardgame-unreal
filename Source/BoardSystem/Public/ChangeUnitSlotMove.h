// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitMove.h"
#include "ChangeUnitSlotMove.generated.h"

/**
 * 
 */
UCLASS()
class BOARDSYSTEM_API UChangeUnitSlotMove : public UUnitMove
{
	GENERATED_BODY()
protected:
	virtual void Move(AActor* Target) override;

	virtual bool TargetIsValid(AActor* Target) override;
};