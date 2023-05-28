// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardContainer.h"
#include "MulliganCardWidget.generated.h"


class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMulliganCardCardClicked, UMulliganCardWidget*, Card);

UCLASS()
class UI_API UMulliganCardWidget : public UCardContainer
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CardClicked();

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite)
	bool Selected;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnMulliganCardCardClicked OnCardClicked;
};
