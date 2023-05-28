// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "EmblemContainer.h"
#include "UserStatusContainer.h"
#include "SelectionController.h"

#include "MenuTop.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UMenuTop : public UUserStatusContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* TabsContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_UserName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* Text_UserLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEmblemContainer* Emblem;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuButton;
	
	UPROPERTY(BlueprintReadWrite)
	USelectionController* SelectionController;

    virtual void UpdateContent() override;

	virtual void NativeConstruct() override;
};
