// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserStatusStructs.h"
#include "PlayerStatusContainer.generated.h"

class AMatchPlayerState;
class AMatchPlayerController;
/**
 * 
 */
UCLASS()
class MATCHUI_API UPlayerStatusContainer : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	FPlayerStatus PlayerStatus;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller);

	UFUNCTION(BlueprintCallable)
	virtual void SetStatus(FPlayerStatus NewPlayerStatus);

protected:
	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerController* PlayerController;
};
