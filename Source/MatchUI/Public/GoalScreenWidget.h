// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "GoalScreenWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedGoal);

UCLASS()
class MATCHUI_API UGoalScreenWidget : public UColorContainer
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnim(bool Opponent);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnFinishedGoal OnFinishedTransition;
};
