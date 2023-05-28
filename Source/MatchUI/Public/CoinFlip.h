// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "CoinFlip.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoinFlipFinished);

UCLASS()
class MATCHUI_API UCoinFlip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool First;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnCoinFlipFinished OnCoinFlipFinished;
	
	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimCoinFlip;

	UFUNCTION(BlueprintCallable)
	void PlayCoinFlip(bool FirstPlayer);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
    void OnUpdateFirst(bool FirstPlayer);

};
