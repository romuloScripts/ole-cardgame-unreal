// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "UObject/Object.h"
#include "WidgetComponentCustomCollision.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class BOARDSYSTEM_API UWidgetComponentCustomCollision : public UWidgetComponent
{
	GENERATED_BODY()

public:

	virtual FCollisionShape GetCollisionShape(float Inflation) const override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateCollision();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D CollisionArea = FVector2D(500,500);
};
