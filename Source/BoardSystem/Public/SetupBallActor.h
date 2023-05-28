﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SetupBallActor.generated.h"

class ABallActor;
// This class does not need to be modified.
UINTERFACE()
class USetupBallActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOARDSYSTEM_API ISetupBallActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Setup(ABallActor* BallActor);
};