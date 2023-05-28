// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MatchmakingPlayerPanel.h"
#include "Blueprint/UserWidget.h"
#include "MatchmakingWidget.generated.h"

class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedTransition);

UCLASS()
class UI_API UMatchmakingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* Cancel;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnFinishedTransition OnFinishedTransition;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void PlayMatchFoundAnimation();

	UFUNCTION(BlueprintCallable)
	void SetPlayer(FPlayerStatus PlayerStatus);

	UFUNCTION(BlueprintCallable)
	void SetOpponent(FPlayerStatus OpponentStatus);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UMatchmakingPlayerPanel* PlayerPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UMatchmakingPlayerPanel* OpponentPanel;
};
