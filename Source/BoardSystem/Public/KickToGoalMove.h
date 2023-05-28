// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallMove.h"
#include "KickToGoalMove.generated.h"

class AGoalkeeperActor;

UCLASS()
class BOARDSYSTEM_API UKickToGoalMove : public UBallMove
{
	GENERATED_BODY()
public:
	virtual bool InteractionAllowed(AActor* Target) override;

	virtual void ResetPoints() override;

protected:

	UFUNCTION()
	void BallReached();
	
	UFUNCTION()
	void BallReturned();
	
	virtual void Move(AActor* Target) override;
	
	virtual bool TargetIsValid(AActor* Target) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int GetMaxKicks() const;

	bool ReachedMaxKicks() const;

	UPROPERTY(BlueprintReadWrite,Replicated,VisibleAnywhere)
	int NumKicks;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	int MaxKicks = 1;

	UPROPERTY()
	AGoalkeeperActor* Goalkeeper;
};
