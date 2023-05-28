// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "MenuTop.h"
#include "Components/WidgetSwitcher.h"
#include "UserStatusContainer.h"
#include "MenuSwitcherParams.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* Menu_WidgetSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMenuTop* Menu_Top;

	void CreateSwitcherParams(int i, UMenuSwitcherParams* SwitcherParams);
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMenuSwitcherParams*> MenuSwitcherParams;
};
