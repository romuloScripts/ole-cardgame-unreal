// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Blueprint/UserWidget.h"
#include "Selectable.h"
#include "SelectEvent.h"
#include "CardFilterWidget.generated.h"

class UIconsPreset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendCardClass, ECardClass, CardClass, bool, Selected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendCardType, ECardType, CardType, bool, Selected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendCardRarity, ERarityType, CardRarity, bool, Selected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendCardCost, int, CardCost, bool, Selected);

UCLASS(BlueprintType)
class UI_API UCardFilterWidget : public UUserWidget, public ISelectable 
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendCardClass OnSendCardClass;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendCardType OnSendCardType;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendCardRarity OnSendCardRarity;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendCardCost OnSendCardCost;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool Selected;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor SelectedBGColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor UnselectedBGColor = FLinearColor::Black;
	
	UPROPERTY(BlueprintReadWrite,Category=Default)
	USelectEvent* SelectEvent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	UIconsPreset* IconsPreset;

	UPROPERTY(BlueprintReadWrite, Category=Default, meta = (BindWidget))
	UButton* Button_filter;

	virtual void NativeConstruct() override;

	virtual void Unselect_Implementation() override;

	virtual  void Select_Implementation() override;

	virtual bool IsSelectedState_Implementation() override;

	virtual USelectEvent* GetSelectEvent_Implementation() override;

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnPosClicked();

	UFUNCTION(BlueprintCallable)
	void OnClicked();
};
