// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "TeamFormationWidget.generated.h"

class AMatchPlayerState;
class AMatchPlayerController;
/**
 * 
 */
UCLASS()
class MATCHUI_API UTeamFormationWidget : public UColorContainer
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerController* OwnerPlayerController;

	UFUNCTION(BlueprintCallable)
	void SetUser(AMatchPlayerController* PlayerController, AMatchPlayerState* PlayerState);
	
};
