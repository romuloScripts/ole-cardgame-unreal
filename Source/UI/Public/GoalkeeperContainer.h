// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ColorContainer.h"
#include "UObject/Object.h"
#include "GoalkeeperContainer.generated.h"

class UGoalkeepersPreset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickedEventSendGoalkepper, UGoalkeepersPreset*, Goalkeeper);

UCLASS()
class UI_API UGoalkeeperContainer : public UColorContainer
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateGoalkeeper(UGoalkeepersPreset* NewGoalkeepersPreset);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateGoalkeeper(UGoalkeepersPreset* NewGoalkeepersPreset);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UGoalkeepersPreset* GoalkeepersPreset;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FClickedEventSendGoalkepper EventSendGoalkepper; 
};
