// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardSelectorWidgetBase.h"
#include "ActionScreenWidget.generated.h"

class UActionInfoWidget;
/**
 * 
 */
UCLASS()
class MATCHUI_API UActionScreenWidget : public UBoardSelectorWidgetBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UActionInfoWidget* ActionInfo;
	
	virtual void ShowActionInfo(FVector WorldPos, int Cost, const FText& Action, bool Blocked) override;
	virtual void HideActionInfo() const override;
	virtual bool IsHidden() const override;
};
