// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallMove.h"
#include "PassBallMove.generated.h"

/**
 * 
 */
UCLASS()
class BOARDSYSTEM_API UPassBallMove : public UBallMove
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxDistance = 2;
	
	virtual bool InteractionAllowed(AActor* Target) override;
protected:
	virtual void Move(AActor* Target) override;

	virtual bool TargetIsValid(AActor* Target) override;
};
