// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBadgeWidget.h"

#include "CardPreset.h"
#include "ColorPreset.h"
#include "IconsPreset.h"

void UCardBadgeWidget::UpdateCard(UCardPreset* NewCardPreset, int CardLevel)
{
	if(NewCardPreset == nullptr) return;
	CardPreset = NewCardPreset;
	level = CardLevel;
	OnUpdateCard(NewCardPreset, CardLevel);

	if(IconsPreset)
	{
		UTexture2D* BgTexture = IconsPreset->TypeMap[CardPreset->CardType].BgTexture;
		Bg->SetBrushFromTexture(BgTexture);
		Outline->SetBrushFromTexture(BgTexture);
		Bg_Color1->SetBrushFromTexture(BgTexture);
	}
	
	Bg_ColorBW->SetBrushFromTexture(NewCardPreset->Texture1);
	Bg_Color2->SetBrushFromTexture(NewCardPreset->Texture2);
	ManaCost_Text->SetText(FText::AsNumber(CardPreset->ManaCost));
}

void UCardBadgeWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	Bg_Color1->SetColorAndOpacity(ColorPreset->Color1);
	ManaCostBG->SetColorAndOpacity(ColorPreset->Color1);
	Bg_Color2->SetColorAndOpacity(ColorPreset->Color2);
}

