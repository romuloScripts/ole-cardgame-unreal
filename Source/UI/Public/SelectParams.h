// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SelectParams.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectEvent,UObject*,Selectable);

UCLASS()
class UI_API USelectParams : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UObject* Selectable;

	UFUNCTION(BlueprintCallable)
	void Init(UObject* ISelectable);

	UFUNCTION(BlueprintCallable)
    void Selected();

	UPROPERTY(BlueprintAssignable)
	FOnSelectEvent OnSelectEvent;
};
