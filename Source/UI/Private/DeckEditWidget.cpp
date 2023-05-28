// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckEditWidget.h"

#include "CardFunctionLibrary.h"
#include "CardMenuItemWidget.h"
#include "DataFunctionLibrary.h"
#include "DeckFunctionLibrary.h"

void UDeckEditWidget::PostUpdateDeck()
{

	if(IsDesignTime()) return;
	
	for (auto Badge : BadgeWidgets)
	{
		Badge->ShowOutline = true;
		Badge->OnClickToRemove.AddDynamic(this,&UDeckEditWidget::RemoveCard);
		Badge->OnClickToAdd.AddDynamic(this,&UDeckEditWidget::AddCard);
	}
	
	for (auto Unit : UnitWidgets)
	{
		Unit->ShowOutline = true;
		Unit->OnClickToRemove.AddDynamic(this,&UDeckEditWidget::RemoveCard);
		Unit->OnClickToAdd.AddDynamic(this,&UDeckEditWidget::AddCard);
	}
}

void UDeckEditWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CardsSide->FilterByClass(DeckData.CardClass,true);
	
	
	if(EditableTextBox_DeckName)
	{
		EditableTextBox_DeckName->OnTextCommitted.AddDynamic(this,&UDeckEditWidget::UpdateNameText);
		EditableTextBox_DeckName->SetText(FText::FromName(DeckData.DeckName));
	}

	if(Button_Ready)
		Button_Ready->OnClicked.AddDynamic(this,&UDeckEditWidget::OnReady);

	if(Goalkeeper_Button)
	{
		Goalkeeper_Button->OnClicked.AddDynamic(this,&UDeckEditWidget::GoalkepperClicked);
		Goalkeeper_Button->OnHovered.AddDynamic(this,&UDeckEditWidget::GoalkepperHovered);
		Goalkeeper_Button->OnUnhovered.AddDynamic(this,&UDeckEditWidget::GoalkepperUnhovered);
	}
	
	if(CardsSide->Cards.Num() > 0)
	{
		BindAndUpdateCardsAmount(CardsSide->Cards);
	}
	CardsSide->OnSendCards.AddDynamic(this,&UDeckEditWidget::BindAndUpdateCardsAmount);
}

void UDeckEditWidget::OnReady()
{
	FDeckCardsAmount CardsAmount;
	UDeckFunctionLibrary::GetDeckCardsAmount(DeckData ,CardsAmount);
	int32 Result=0;
	UDeckFunctionLibrary::IsDeckValid(CardsAmount,Result);
	if(TEST_NONE(Result))
	{
		SetSaveDialogBox(SaveDeckDialog);
	}else
	{
		SetSaveDialogBox(SaveInvalidDeckDialog);
	}
}

void UDeckEditWidget::UpdateCardAmount(UCardContainer* Card)
{
	const auto CardMenuItem = Cast<UCardMenuItemWidget>(Card);
	if(!CardMenuItem) return;
	int Unlocked = 0, Used =0;
	bool ContainsCard;
	SetUnlockedAndUsed(CardMenuItem->CardPreset,Unlocked,Used,ContainsCard);
	CardMenuItem->SetAmountAndMax(Unlocked,Used);
}

void UDeckEditWidget::UpdateCardAmountByPreset(UCardPreset* Card)
{
	for (const auto CardContainer : CardsSide->Cards)
	{
		if(CardContainer->CardPreset == Card)
		{
			UpdateCardAmount(CardContainer);
			return;
		}
	}
}

void UDeckEditWidget::BindAndUpdateCardsAmount(TArray<UCardContainer*> Cards)
{
	for (auto Card : Cards)
	{
		const auto CardMenuItem = Cast<UCardMenuItemWidget>(Card);
		if(!CardMenuItem) return;
		CardMenuItem->OnClickedEventCardItemMenu.AddDynamic(this,&UDeckEditWidget::AddCardByMenuItemWidget);
	}
	UpdateCardsAmount(Cards);
}

void UDeckEditWidget::UpdateCardsAmount(TArray<UCardContainer*> Cards)
{
	for (const auto Card : Cards)
	{
		UpdateCardAmount(Card);
	}
}

void UDeckEditWidget::SetSaveDialogBox(TSubclassOf<USaveDeckDialogWidget> SubclassOf)
{
	USaveDeckDialogWidget* DialogBox = CreateWidget<USaveDeckDialogWidget>(this,SubclassOf);
	DialogBox->AddToViewport();
	if(DialogBox->Button_Save)
	{
		DialogBox->Button_Save->OnClicked.AddDynamic(this,&UDeckEditWidget::SaveDeck);
	}

	if(DialogBox->Button_Discard)
	{
		DialogBox->Button_Discard->OnClicked.AddDynamic(this,&UDeckEditWidget::DiscardDeck);
	}
}

void UDeckEditWidget::SaveDeck()
{
	if(UserStatusController)
	{
		if(EditableTextBox_DeckName && EditableTextBox_DeckName->GetText().ToString() != DeckData.DeckName.ToString())
		{
			UserStatusController->RemoveDeck(DeckData.DeckName);
			DeckData.DeckName = FName(EditableTextBox_DeckName->GetText().ToString());
		}
		UserStatusController->AddDeck(DeckData);
	}
	RemoveFromParent();
}

void UDeckEditWidget::DiscardDeck()
{
	RemoveFromParent();
}

void UDeckEditWidget::UpdateNameText(const FText& NameText,ETextCommit::Type Commit)
{
	if(UserStatusController->DeckExist(FName(NameText.ToString())))
	{
		if(EditableTextBox_DeckName)
			EditableTextBox_DeckName->SetText(FText::FromName(DeckData.DeckName));
	}
}

void UDeckEditWidget::SetUnlockedAndUsed(UCardPreset* Card, int& Unlocked, int& Used,bool& ContainsCard)
{
	if(UserStatus.Cards.Contains(Card))
		Unlocked = UserStatus.Cards[Card];

	const auto CardInDeck = UDeckFunctionLibrary::FindCardInDeck(DeckData,Card);
	if(CardInDeck)
	{
		Used = UDeckFunctionLibrary::GetCardAmountInDeck(CardInDeck,DeckData);
		ContainsCard = true;
	}else
	{
		ContainsCard = false;
	}
}

void UDeckEditWidget::AddCardByMenuItemWidget(UCardMenuItemWidget* CardItemWidget)
{
	UCardPreset* Card = CardItemWidget->CardPreset;
	if(Card == nullptr) return;
	const auto Result = TryAddCard(Card);
	CardItemWidget->PlayFeedbackAnimation(Result);
}

EAddCardDeniedType UDeckEditWidget::TryAddCard(UCardPreset* Card)
{
	if(Card == nullptr) return EAddCardDeniedType::None;
	FDeckCardsAmount CardsAmount;
	UDeckFunctionLibrary::GetDeckCardsAmount(DeckData,CardsAmount);
	int Unlocked=0;
	int Used=0;
	bool ContainsCard;
	SetUnlockedAndUsed(Card,Unlocked,Used,ContainsCard);
	const auto Result = UDeckFunctionLibrary::AllowAddCardToDeck(Card,Used,Unlocked,CardsAmount,ContainsCard);
	
	if(Result != EAddCardDeniedType::None)
	{
		if(Notification && NotificationTextMap.Contains(Result))
		{
			const auto NewNotification = CreateWidget<UNotificationContainer>(this,Notification);
			NewNotification->AddToViewport();
			NewNotification->SetNotification(NotificationTextMap[Result]);
		}
	}else
	{
		const int index = UDeckFunctionLibrary::FindCardIndexInDeck(DeckData,Card);
		if(index < 0)
		{
			FCardInDeck CardInDeck;
			CardInDeck.Card =Card;
			CardInDeck.Amount = UCardFunctionLibrary::IsUnitCard(Card) ? 0 : 1;
			DeckData.Cards.Add(CardInDeck);
		}
		else DeckData.Cards[index].Amount++;

		UpdateDeck(DeckData);
		UpdateCardAmountByPreset(Card);
	}
	return Result;
}

void UDeckEditWidget::AddCard(UCardPreset* Card)
{
	TryAddCard(Card);
}

void UDeckEditWidget::RemoveCard(UCardPreset* Card)
{
	const int index = UDeckFunctionLibrary::FindCardIndexInDeck(DeckData,Card);
	if(index < 0) return;
	if(DeckData.Cards[index].Amount >1 || (UCardFunctionLibrary::IsUnitCard(Card) && DeckData.Cards[index].Amount > 0))
	{
		DeckData.Cards[index].Amount--;
	}else
	{
		DeckData.Cards.RemoveAt(index);
	}
	UpdateDeck(DeckData);
	UpdateCardAmountByPreset(Card);
}

void UDeckEditWidget::GoalkepperClicked()
{
	CardsSide->ShowGoalkeppers();
	for (const auto GoalkeeperItem: CardsSide->Goalkeepers)
	{
		GoalkeeperItem->EventSendGoalkepper.AddDynamic(this,&UDeckEditWidget::ChangeDeckGoalkepper);
	}
}

void UDeckEditWidget::GoalkepperHovered()
{
	if(Goalkeeper)
		Goalkeeper->Outline->SetVisibility(ESlateVisibility::HitTestInvisible);
	const auto UserColor = UDeckFunctionLibrary::GetCustomization(UserStatus).ColorPalette;
	if(GoalkeeperColor && UserColor)
		GoalkeeperColor->SetColorAndOpacity(UserColor->Color2);
}

void UDeckEditWidget::GoalkepperUnhovered()
{
	const auto Color = UDeckFunctionLibrary::GetCustomization(UserStatus).ColorPalette;
	if(Goalkeeper)
		Goalkeeper->Outline->SetVisibility(ESlateVisibility::Hidden);
	if(GoalkeeperColor && Color)
		GoalkeeperColor->SetColorAndOpacity(Color->Color1);
}

void UDeckEditWidget::ChangeDeckGoalkepper(UGoalkeepersPreset* Preset)
{
	DeckData.GoalkeeperPreset = Preset;
	UpdateDeck(DeckData);
	CardsSide->FilterByClass(DeckData.CardClass,true);
}
