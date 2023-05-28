// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Phase.h"
#include "MulliganPhase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MATCH_API UMulliganPhase : public UPhase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MulliganMaxTime = 20;
	
	UFUNCTION()
	void StartMulligan();
	
	virtual void OnBegin(const FGameContext& Context) override;

	virtual bool EndIf() override;

	virtual void UpdatePhase(float Delta) override;
};
