// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "MenuSwitcherParams.h"
#include "SelectionController.h"
#include "UObject/Object.h"
#include "MenuTabs.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UMenuTabs : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* TabsContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* MenuWidgetSwitcher;

	UPROPERTY(BlueprintReadWrite)
	USelectionController* SelectionController;

private:

	UPROPERTY()
	TArray<UMenuSwitcherParams*> MenuSwitcherParams;
};
