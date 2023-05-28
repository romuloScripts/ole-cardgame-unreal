// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "UserStatusStructs.h"
#include "ColorContainer.h"
#include "MulliganWidget.generated.h"

class UMulliganCardWidget;
struct FCardWithLevel;
class AMatchPlayerController;
class AMatchPlayerState;

UCLASS()
class MATCHUI_API UMulliganWidget : public UColorContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	FPlayerStatus User;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	TSubclassOf<UMulliganCardWidget> CardClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	FMargin CardsMargin = FMargin(12,0,12,0);

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UHorizontalBox* CardsPanel;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category=Default)
	TArray<FCardWithLevel> CardsEditor;

	UPROPERTY(BlueprintReadWrite, Category=Default)
	TArray<UMulliganCardWidget*> CardsInstances;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerController* OwnerPlayerController;

	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    void SetCards(TArray<FCardWithLevel> Cards);

	UFUNCTION(BlueprintCallable)
	void AddCard(const FCardWithLevel& CardWithLevel);

	UFUNCTION(BlueprintCallable)
    void SetUser(AMatchPlayerController* PlayerController, AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable)
    void GetReplaceCards(TArray<int>& Cards);
};
