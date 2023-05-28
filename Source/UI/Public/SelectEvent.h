// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Button.h"
#include "UObject/Object.h"
#include "SelectEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickedEventSendObject, UObject*, Object);


UCLASS(BlueprintType)
class UI_API USelectEvent : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnButtonClickedEvent OnSelected;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FClickedEventSendObject OnClicked;
};