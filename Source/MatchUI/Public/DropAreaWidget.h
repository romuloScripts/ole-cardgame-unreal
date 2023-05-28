// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropAreaWidget.generated.h"

class AMatchPlayerState;
class UHandWidget;
/**
 * 
 */
UCLASS()
class MATCHUI_API UDropAreaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION(BlueprintCallable)
	void SetReferences(UHandWidget* Hand,AMatchPlayerState* Player);
	
protected:
	UPROPERTY(BlueprintReadWrite)
	UHandWidget* HandRef;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;
};
