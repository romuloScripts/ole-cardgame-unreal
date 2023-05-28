// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "CardsShowcaseWidget.h"
#include "DeckPreviewWidget.h"
#include "GoalkeeperWidget.h"
#include "SaveDeckDialogWidget.h"
#include "CardMenuItemWidget.h"
#include "NotificationContainer.h"
#include "UObject/Object.h"
#include "DeckEditWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UDeckEditWidget : public UDeckPreviewWidget
{
	GENERATED_BODY()

public:

	virtual void PostUpdateDeck() override;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnReady();

	UFUNCTION(BlueprintCallable)
	void UpdateCardAmount(UCardContainer* Card);

	UFUNCTION(BlueprintCallable)
	void BindAndUpdateCardsAmount(TArray<UCardContainer*> Cards);

	UFUNCTION(BlueprintCallable)
	void UpdateCardAmountByPreset(UCardPreset* Card);

	UFUNCTION(BlueprintCallable)
    void UpdateCardsAmount(TArray<UCardContainer*> Cards);

	UFUNCTION(BlueprintCallable)
    void SetSaveDialogBox(TSubclassOf<USaveDeckDialogWidget> SubclassOf);

	UFUNCTION(BlueprintCallable)
	void SaveDeck();

	UFUNCTION(BlueprintCallable)
    void DiscardDeck();

	UFUNCTION(BlueprintCallable)
	void UpdateNameText(const FText& NameText,ETextCommit::Type Commit);

	UFUNCTION(BlueprintCallable)
	void AddCardByMenuItemWidget(UCardMenuItemWidget* CardItemWidget);

	UFUNCTION(BlueprintCallable)
	EAddCardDeniedType TryAddCard(UCardPreset* Card);

	UFUNCTION(BlueprintCallable)
	void AddCard(UCardPreset* Card);

	UFUNCTION(BlueprintCallable)
	void SetUnlockedAndUsed(UCardPreset* Card,int& Unlocked,int& Used,bool& ContainsCard);

	UFUNCTION(BlueprintCallable)
	void RemoveCard(UCardPreset* Card);

	UFUNCTION(BlueprintCallable)
	void GoalkepperClicked();

	UFUNCTION(BlueprintCallable)
    void GoalkepperHovered();

	UFUNCTION(BlueprintCallable)
    void GoalkepperUnhovered();

	UFUNCTION(BlueprintCallable)
    void ChangeDeckGoalkepper(UGoalkeepersPreset* Preset);

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UEditableTextBox* EditableTextBox_DeckName;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Button_Ready;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UButton* Goalkeeper_Button;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UGoalkeeperWidget* Goalkeeper;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCardsShowcaseWidget* CardsSide;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TMap<EAddCardDeniedType,FText> NotificationTextMap; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<USaveDeckDialogWidget> SaveDeckDialog;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<USaveDeckDialogWidget> SaveInvalidDeckDialog;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<UNotificationContainer> Notification;
};
