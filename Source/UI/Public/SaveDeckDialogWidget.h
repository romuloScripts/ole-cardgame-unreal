// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "SaveDeckDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API USaveDeckDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Button_Save;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Button_Cancel;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Button_Discard;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Background;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void RemoveParent();
};
