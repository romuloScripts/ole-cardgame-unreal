// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "ManaBarWidget.generated.h"

class UImage;
class UTextBlock;
class UHorizontalBox;
class UManaCellWidget;
class AMatchPlayerState;
class AMatchPlayerController;

UCLASS()
class MATCHUI_API UManaBarWidget : public UColorContainer
{
	GENERATED_BODY()

public:
	
	virtual void NativePreConstruct() override;

	void UpdateText(int Remain, int Max) const;

	UFUNCTION(BlueprintCallable)
	bool UpdateManaMax(int Max);

	UFUNCTION(BlueprintCallable)
	void SetPlayer(AMatchPlayerState* NewPlayerState,AMatchPlayerController* NewPlayerController);

	UFUNCTION(BlueprintCallable, Category = Mana)
	void UpdateMana(int Remain, int Max);

	UFUNCTION(BlueprintCallable, Category = Mana)
	void UpdateCanSpentMana(int Value);

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<UManaCellWidget> ManaCellWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FMargin ManaPadding = FMargin(2,0,2,0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int ManaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int ManaCurrentCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int ManaMaxCurrentCount;

	UPROPERTY(BlueprintReadWrite, Category = "Mana")
	TArray<UManaCellWidget*> ManaArray;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UHorizontalBox* BallPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ManaCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UImage* ManaBarBg;
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	AMatchPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	AMatchPlayerController* PlayerController;
};
