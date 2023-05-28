// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "NotificationContainer.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UI_API UNotificationContainer : public UUserWidget
{
	GENERATED_BODY()

public :

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default,meta=(UIMin=0.1f))
	float AnimSpeed =1;

	UFUNCTION(BlueprintImplementableEvent)
	void SetNotification(const FText& NewText);
};
