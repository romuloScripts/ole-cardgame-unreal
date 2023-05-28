// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "HudWidget.generated.h"

class UCardPlayedWidget;
class UOverlay;
class AMatchPlayerController;
class AMatchGameState;
class AMatchPlayerState;

UCLASS()
class MATCHUI_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UCardPlayedWidget* CardPlayedPlayer;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartStates(AMatchPlayerController* PlayerController, AMatchPlayerState* Player, AMatchPlayerState* Opponent);

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* HudOverlay;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* OpponentState;

	UPROPERTY(BlueprintReadWrite)
	AMatchGameState* GameState;
};
