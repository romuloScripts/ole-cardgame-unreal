// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SetupSoccerActor.generated.h"

class ASoccerActor;
// This class does not need to be modified.
UINTERFACE()
class USetupSoccerActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOARDSYSTEM_API ISetupSoccerActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Setup(ASoccerActor* UnitActor);
};
