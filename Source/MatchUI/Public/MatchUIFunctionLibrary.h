// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatchUIFunctionLibrary.generated.h"

class UMatchHUD;
class UHudWidget;
/**
 * 
 */
UCLASS()
class MATCHUI_API UMatchUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category=Widget,Meta=(DefaultToSelf="Instigator"),BlueprintPure)
	static UHudWidget* GetHudWidget(UObject* Instigator);

	UFUNCTION(BlueprintCallable,Category=Widget,Meta=(DefaultToSelf="Instigator"),BlueprintPure)
	static UMatchHUD* GetPlayerHud(UObject* Instigator);
};
