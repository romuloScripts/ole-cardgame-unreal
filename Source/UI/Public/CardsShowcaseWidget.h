// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UserStatusContainer.h"
#include "CardsShowcaseWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UCheckBox;
class UButton;
class USelectionController;
class UCardContainer;
class UGoalkeeperContainer;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSendCardsDelegate, TArray<UCardContainer*>, Cards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSendGoalkeppersDelegate, TArray<UGoalkeeperContainer*>, Goalkeepers);

UCLASS()
class UI_API UCardsShowcaseWidget : public UUserStatusContainer
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateSearchText(const FText& SearchText,ETextCommit::Type Commit);

	UFUNCTION(BlueprintCallable)
	void UpdateShowAll(bool bIsChecked);

	UFUNCTION(BlueprintCallable)
    void TopBarShow();
    
	UFUNCTION(BlueprintCallable)
    void TopBarFilterShow();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
    void ShowGoalkeppers();

	UFUNCTION(BlueprintCallable)
    void FilterByClass(ECardClass CardClass, bool Selected);

	UFUNCTION(BlueprintCallable)
    void FilterByType(ECardType CardType, bool Selected);

	UFUNCTION(BlueprintCallable)
    void FilterByRarity(ERarityType CardRarity, bool Selected);

	UFUNCTION(BlueprintCallable)
    void FilterByCost(int CardCost, bool Selected);

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendCardsDelegate OnSendCards;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FSendGoalkeppersDelegate OnSendGoalkeppers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<UCardContainer*> Cards;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<UGoalkeeperContainer*> Goalkeepers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	ECardClass CardClassFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	ECardType CardTypeFilter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	ERarityType CardRarityFilter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool ShowAll;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool FilterCost;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default, meta = (ClampMin = 0))
	int CostFilter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FText Search;

	UPROPERTY(BlueprintReadWrite,Category=Default)
	FSlateColor ShowAllTextNormalColor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FSlateColor ShowAllTextSelectedColor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UEditableTextBox* EditableTextBox_Search;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UCheckBox* ShowAll_CheckBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UTextBlock* ShowAll_Text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UButton* Button_Filter_ToggleOff;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UButton* Button_Filter_ToggleOn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UWidget* TopBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UWidget* TopBarFilters;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UPanelWidget* FilterClassContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UPanelWidget* FilterTypeContainer;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UPanelWidget* FilterRarityContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UPanelWidget* FilterCostContainer;

	UPROPERTY(BlueprintReadWrite)
	USelectionController* ClassSelectionController;

	UPROPERTY(BlueprintReadWrite)
	USelectionController* TypeSelectionController;

	UPROPERTY(BlueprintReadWrite)
	USelectionController* RaritySelectionController;

	UPROPERTY(BlueprintReadWrite)
	USelectionController* CostSelectionController;
};
