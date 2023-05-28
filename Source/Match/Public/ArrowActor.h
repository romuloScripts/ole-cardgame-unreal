// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowActor.generated.h"

UCLASS()
class MATCH_API AArrowActor : public AActor
{
	GENERATED_BODY()

public:
	AArrowActor();

	UFUNCTION(BlueprintImplementableEvent)
	void SetPos(const FVector Origin,const FVector Target);

	UFUNCTION(BlueprintImplementableEvent)
	void Hide();
};
