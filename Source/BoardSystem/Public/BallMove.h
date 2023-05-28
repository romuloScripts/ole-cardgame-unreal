// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Move.h"
#include "BallMove.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOARDSYSTEM_API UBallMove : public UMove
{
	GENERATED_BODY()

protected:

	virtual bool TargetIsValid(AActor* Target) override;
};
