// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetSwitcher.h"
#include "UObject/Object.h"
#include "MenuSwitcherParams.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UMenuSwitcherParams : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	int menuIndex;

	UPROPERTY(BlueprintReadWrite)
	UWidgetSwitcher* Menu_WidgetSwitcher;

	UFUNCTION(BlueprintCallable)
    void ChangeMenuTab();

	
};
