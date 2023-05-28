// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardTargetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract,EditInlineNew)
class DATA_API UCardTargetBase : public UObject
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override { return true; }
};
