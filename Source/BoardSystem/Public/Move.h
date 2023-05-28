// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Move.generated.h"


class ASoccerActor;

UCLASS(Abstract,Blueprintable,BlueprintType)
class BOARDSYSTEM_API UMove : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Replicated)
	int CurrentManaCost;

	void SetOwner(ASoccerActor* Target);

	virtual FText GetActionInfo();

	bool ValidTarget(AActor* Target);

	bool Allowed(AActor* Target);

	bool Invoke(AActor* Target);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override { return true; }

	virtual void ResetPoints();

	bool HaveMana() const;

	UFUNCTION()
	bool InPossessOfBall() const;
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	int ManaCost=1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FText ActionInfo = FText(FText::FromString("Move")); 
	
	UPROPERTY(BlueprintReadWrite,Category=Default,Replicated)
	ASoccerActor* OwnerActor;

	virtual void PostSetOwner(ASoccerActor* Target);

	virtual bool InteractionAllowed(AActor* Target);
	
	virtual void Move(AActor* Target);

	virtual bool TargetIsValid(AActor* Target);

	UFUNCTION()
	virtual void EndMove();
};
