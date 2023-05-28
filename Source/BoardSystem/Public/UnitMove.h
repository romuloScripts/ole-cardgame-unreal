// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Move.h"
#include "UObject/Object.h"
#include "UnitMove.generated.h"

class AUnitActor;
/**
 * 
 */
UCLASS(Abstract)
class BOARDSYSTEM_API UUnitMove : public UMove
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	
protected:

	UPROPERTY(Replicated)
	AUnitActor* UnitActor;

	virtual bool TargetIsValid(AActor* Target) override;

	virtual void PostSetOwner(ASoccerActor* Target) override;
};
