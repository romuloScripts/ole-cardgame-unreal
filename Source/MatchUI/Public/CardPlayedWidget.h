// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardPlayedWidgetBase.h"
#include "Components/Image.h"
#include "CardPlayedWidget.generated.h"

class UCardSelectTarget;
class UCard;
class UCardTargetWidget;
class AMatchPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardEndUsed);

UCLASS()
class MATCHUI_API UCardPlayedWidget : public UCardPlayedWidgetBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	bool CardUsed;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	float DisplayTime = 1.5f;

	UPROPERTY(BlueprintReadWrite)
	bool Opponent;

	UFUNCTION(BlueprintCallable)
	void UpdateCard(UCard* NewCard);

	UFUNCTION(BlueprintCallable)
	void PlayCard(UCard* NewCard);

	UFUNCTION(BlueprintCallable)
	void OnCardUsed(UCard* NewCard);

	UFUNCTION(BlueprintCallable)
	void OnWaitCardTargets(UCard* NewCard,UCardSelectTarget* CardTarget);

	UFUNCTION(BlueprintCallable)
	void OnCancelWaitCardTargets(UCard* NewCard);

	UFUNCTION(BlueprintCallable)
	FVector GetCardWidgetArrowOriginPos();

	void BindAnimIn();
	void BindAnimOut();
	void UnbindAnimIn();
	void UnbindAnimOut();
	
	virtual void NativeConstruct() override;
	void CreateTargetWidget();
	void RemoveTargetWidget();
	void UpdateTargetWidget();
	void Clear();
	void HideInfo();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void FinishedCardUsed();

	virtual void SetUser(AMatchPlayerState* Player, bool IsOpponent) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	FText TrapCardDescription;
	
	UPROPERTY()
	UCard* CurrentCard;

	UPROPERTY()
	bool WaitConfirm;

	UPROPERTY()
	FTimerHandle Timer;

	UPROPERTY()
	FWidgetAnimationDynamicEvent AnimEndEventIn;

	UPROPERTY()
	FWidgetAnimationDynamicEvent AnimEndEventOut;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_In;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_Out;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_In_Opponent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_In_Opponent_Trap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_Out_Opponent_Trap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* TargetWidgetPanel;

	UPROPERTY(BlueprintReadWrite)
	UCardTargetWidget* TargetWidget;

	UFUNCTION(BlueprintCallable)
	void OnPlayAnimEnd();

	UFUNCTION(BlueprintCallable)
	void PlayCardOut();

	UFUNCTION(BlueprintCallable)
	void FinishedIn();

	UFUNCTION(BlueprintCallable)
	void FinishedOut();
};
