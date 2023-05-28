// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "EmblemContainer.h"
#include "Data/Public/UserStatusStructs.h"
#include "MatchmakingPlayerPanel.generated.h"

class UCardPreset;
class UIconsPreset;
class UUnitWidget;

UCLASS()
class UI_API UMatchmakingPlayerPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
    void UpdateUser(const FPlayerStatus UserStatus,bool ReserveColor);
    
	UFUNCTION(BlueprintCallable)
    void PlayAnimEmblem();

	UFUNCTION(BlueprintCallable)
    void PlayAnimTeam();

	UFUNCTION(BlueprintCallable)
    void PlayTransition();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* UnitPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Username;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Level;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerColor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Class;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEmblemContainer* Emblem;

	UPROPERTY(BlueprintReadWrite)
	TArray<UUnitWidget*> UnitArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool RightSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FPlayerStatus User;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<UUnitWidget> Unit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UIconsPreset* Icons;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimEmblem;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimTeamLeft;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimTeamRight;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimTransitionLeft;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimTransitionRight;
};
