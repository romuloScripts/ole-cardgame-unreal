// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardWidget.h"
#include "CardContainer.h"
#include "CardMenuItemWidget.generated.h"

enum class EAddCardDeniedType : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickedEventCardItemMenu, UCardMenuItemWidget*, CardMenuItem);

UCLASS()
class UI_API UCardMenuItemWidget : public UCardContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	TSubclassOf<UUserWidget> MarkerUsed;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	TSubclassOf<UUserWidget> MarkerFull;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Default)
	TSubclassOf<UUserWidget> MarkerEmpty;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* CardItemButton;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UCardWidget* BP_Card;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UHorizontalBox* AmountContainer;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HoverIn_Anim;

	UPROPERTY(BlueprintReadOnly,Transient,meta = (BindWidgetAnim))
	UWidgetAnimation* HoverOut_Anim;
	
	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Deny_Anim;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AddToDeck_Anim;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FClickedEventCardItemMenu OnClickedEventCardItemMenu;

	UFUNCTION(BlueprintCallable)
	void SetAmountAndMax(int Unlocked,int Used);

	UFUNCTION(BlueprintCallable)
	void HideAmount();
	

	UFUNCTION(BlueprintCallable)
	void LockImageVisibility(int Amount);

	UFUNCTION(BlueprintCallable)
	void Unhovered();

	UFUNCTION(BlueprintCallable)
    void Hovered();

	UFUNCTION(BlueprintCallable)
    void OnClicked();
	
	UFUNCTION(BlueprintCallable)
    void PlayFeedbackAnimation(const EAddCardDeniedType AddCardDeniedType);

	virtual void NativeConstruct() override;
};
