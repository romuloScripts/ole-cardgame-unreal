// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Phase.h"
#include "UObject/Object.h"
#include "EndMatchmakingPhase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MATCH_API UEndMatchmakingPhase : public UPhase
{
	GENERATED_BODY()
public:
	
	void EndMatchmakingScreen();
	
	virtual void OnBegin(const FGameContext& Context) override;

	virtual bool EndIf() override;
};
