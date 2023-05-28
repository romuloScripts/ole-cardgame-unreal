// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"

enum class EPlayerVictoryState : uint8;
class AMatchPlayerState;

UCLASS()
class MATCHUI_API UVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION()
	void ShowScreen(const EPlayerVictoryState PlayerWinState, const AMatchPlayerState* Player, const AMatchPlayerState* Opponent);

	UFUNCTION(BlueprintCallable)
	void RemoveScreen();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartAnimation(const EPlayerVictoryState PlayerWinState, const AMatchPlayerState* Player, const AMatchPlayerState* Opponent);
};
