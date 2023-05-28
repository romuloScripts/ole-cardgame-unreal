// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckWidget.h"

#include "DeckFunctionLibrary.h"
#include "ColorPreset.h"
#include "IconsPreset.h"

void UDeckWidget::NativePreConstruct()
{
	UpdateDeck(DeckData);
	Super::NativePreConstruct();
}

void UDeckWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	deckHolder_Back_color->SetColorAndOpacity(ColorPreset->Color1);
	deckHolder_Front_color->SetColorAndOpacity(ColorPreset->Color1);
	Super::UpdateColor(ColorPreset);
}

void UDeckWidget::UpdateDeck(const FDeck& NewDeck)
{
	DeckData = NewDeck;
	int32 ValidMask=0;
	FDeckCardsAmount CardsAmount;
	UDeckFunctionLibrary::GetDeckCardsAmount(DeckData,CardsAmount);
	UDeckFunctionLibrary::IsDeckValid(CardsAmount,ValidMask);
	const bool ValidDeck = TEST_NONE(ValidMask);
	Incomplete = !ValidDeck;
	if(DeckName)
	{
		DeckName->SetText(FText::FromName(DeckData.DeckName));
		DeckName->SetColorAndOpacity(ValidDeck? ColorNameNormal: ColorNameInvalid);
	}

	if(ClassIcon && IconsPreset)
		ClassIcon->SetBrushFromTexture(IconsPreset->ClassMap[DeckData.CardClass].IconTexture);

	if(Alert)
		Alert->SetVisibility(ValidDeck ? ESlateVisibility::Hidden : ESlateVisibility::HitTestInvisible);

	const bool Visible = DeckData.Cards.Num()>0;
	const ESlateVisibility CardVisibility = Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	Card_1->SetVisibility(CardVisibility);
	Card_2->SetVisibility(CardVisibility);
	Card_3->SetVisibility(CardVisibility);
	Card_4->SetVisibility(CardVisibility);

	if(Visible)
	{
		CardPreset = DeckData.Cards.Last().Card;
		Card_1->UpdateCard(CardPreset,0);
	}
}
