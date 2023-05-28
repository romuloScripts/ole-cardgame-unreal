// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "UserStatusContainer.h"
#include "Blueprint/UserWidget.h"
#include "SelectionController.h"

#include "CustomizationContainer.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UCustomizationContainer : public UUserStatusContainer
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnClickedOption(UObject* Selected);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UpdateSelected();

	virtual void OnUpdateContent_Implementation() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool UpdateColor = true;
	
	UPROPERTY(BlueprintReadWrite)
	USelectionController* SelectionController;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* SelectablesContainer;
};
