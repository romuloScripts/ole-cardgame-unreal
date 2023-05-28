// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallMove.h"
#include "GameStateEnums.h"
#include "GoalkeeperPassMove.generated.h"

/**
 * 
 */
UCLASS()
class BOARDSYSTEM_API UGoalkeeperPassMove : public UBallMove
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECardType TargetType = ECardType::Defender;
	
	virtual void Move(AActor* Target) override;

	virtual bool TargetIsValid(AActor* Target) override;
};
