// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckPreviewWidget.h"
#include "DeckFunctionLibrary.h"
#include "WidgetFunctionLibrary.h"
#include "IconsPreset.h"

void UDeckPreviewWidget::OnUpdateContent_Implementation()
{
	UpdateDeck(DeckData);
}

void UDeckPreviewWidget::UpdateDeck(const FDeck& NewDeck)
{
	DeckData = NewDeck;
	if(UserStatus.Decks.Contains(DeckData.DeckName))
	{
		DeckData.CustomizationName = UserStatus.Decks[DeckData.DeckName].CustomizationName;
	}
	
	if(DeckName)
	{
		DeckName->SetText(FText::FromName(DeckData.DeckName));
	}

	if(ClassIcon && IconsPreset)
		ClassIcon->SetBrushFromTexture(IconsPreset->ClassMap[DeckData.CardClass].IconTexture);

	FDeckCardsAmount CardsAmount;
	UDeckFunctionLibrary::GetDeckCardsAmount(DeckData,CardsAmount);
	int32 ValidMask=0;
	UDeckFunctionLibrary::IsDeckValid(CardsAmount,ValidMask);

	if(TotalCards_Text)
	{
		TotalCards_Text->SetText(FText::AsNumber(CardsAmount.TotalCards));
		TotalCards_Text->SetColorAndOpacity(TEST_BIT(ValidMask,EDeckValidType::NoTotalCards)?  TextColorInvalid : TextColorNormal);
	}
		
	if(UnitCardQuantity_Text)
		UnitCardQuantity_Text->SetText(FText::AsNumber(CardsAmount.UnitCards));
	if(EffectsQuantity_Text)
		EffectsQuantity_Text->SetText(FText::AsNumber(CardsAmount.EffectCards));
	if(TrapsQuantity_Text)
		TrapsQuantity_Text->SetText(FText::AsNumber(CardsAmount.TrapCards));
	if(UniqueUnitQuantity_Text)
	{
		UniqueUnitQuantity_Text->SetText(FText::AsNumber(CardsAmount.UniqueUnitCards));
		UniqueUnitQuantity_Text->SetColorAndOpacity(TEST_BIT(ValidMask,EDeckValidType::NoAllUnits)? TextColorInvalid : TextColorNormal);
	}
	
	if(Badges_Grid)
	{
		UWidgetFunctionLibrary::CreateBadgesInGrid(DeckData,BadgeWidget,Badges_Grid, BadgesPerRow,EmptyWidget,EmptySlotColumnId,BadgeWidgets);
	}
	
	TMap<ECardType,UVerticalBox*> VerticalBoxes;
	if(Attackers_VerticalBox)
		VerticalBoxes.Add(ECardType::Attacker, Attackers_VerticalBox);
	if(Defenders_VerticalBox)
		VerticalBoxes.Add(ECardType::Defender, Defenders_VerticalBox);
	if(Midfielders_VerticalBox)
		VerticalBoxes.Add(ECardType::Midfield, Midfielders_VerticalBox);
	UWidgetFunctionLibrary::CreateTeamFormationInVerticalBox(DeckData,UnitWidget,VerticalBoxes,UnitWidgets);
	
	if(UserStatus.Customizations.Contains(DeckData.CustomizationName))
	{
		Customization = UserStatus.Customizations[DeckData.CustomizationName];
	}
	if(GoalkeeperColor && Customization.ColorPalette)
		GoalkeeperColor->SetColorAndOpacity(Customization.ColorPalette->Color1);

	UWidgetFunctionLibrary::UpdatePresetInWidget(this,Customization.ColorPalette,Customization.Uniform,DeckData.GoalkeeperPreset);
	PostUpdateDeck();
	OnPostUpdateDeck();
}

void UDeckPreviewWidget::PostUpdateDeck()
{
}

void UDeckPreviewWidget::OnPostUpdateDeck_Implementation()
{
}
