// Fill out your copyright notice in the Description page of Project Settings.

#include "CardWidget.h"
#include "CardFunctionLibrary.h"
#include "CardPreset.h"
#include "ColorPreset.h"
#include "IconsPreset.h"

void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseEnterEvent.Broadcast(this);
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	MouseExitEvent.Broadcast(this);
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UCardWidget::SetUnitVisibility(ESlateVisibility VisibilityType) const
{
	Unit_CanvasPanel->SetVisibility(VisibilityType);
	UnitTypeBG_SizeBox->SetVisibility(VisibilityType);
	LevelImage->SetVisibility(VisibilityType);
	Points->SetVisibility(VisibilityType);
	Points_SizeBox->SetVisibility(VisibilityType);
	Type_Overlay->SetVisibility(VisibilityType);
}

void UCardWidget::UpdateCard(UCardPreset* NewCardPreset, int num)
{
	if(num < 0 || NewCardPreset == nullptr || !Icons) return;
	CardPreset = NewCardPreset;
	level = num;
	CardNameText->SetText(FText::FromName(NewCardPreset->Name));

	ClassIcon->SetBrushFromTexture(Icons->ClassMap[NewCardPreset->CardClass].IconTexture);
	Frame->SetBrushFromTexture(Icons->TypeMap[NewCardPreset->CardType].FrameTexture);
	TypeIcon_Description->SetBrushFromTexture(Icons->TypeMap[NewCardPreset->CardType].IconTexture);
	RarityImage->SetBrushFromTexture(Icons->RarityMap[NewCardPreset->CardRarity].IconTexture);
	TypeImage->SetBrushFromTexture(Icons->TypeMap[NewCardPreset->CardType].IconTexture);

	const bool bHasLevel = NewCardPreset->CardLevels.Num() > 0 && level > 0;
	level = FMath::Clamp(level,0,NewCardPreset->CardLevels.Num());

	if(UCardFunctionLibrary::IsUnitCard(NewCardPreset))
	{
		UpdateUnit(NewCardPreset);
		UnitTypeBG->SetBrushFromTexture(Icons->TypeMap[NewCardPreset->CardType].BgTexture);
		
		Effect_SizeBox->SetVisibility(ESlateVisibility::Hidden);
		Trap_SizeBox->SetVisibility(ESlateVisibility::Hidden);

		SetUnitVisibility(ESlateVisibility::HitTestInvisible);

		const ESlateVisibility ManaVisibility = bHasLevel ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed;
		ManaCost->SetVisibility(ManaVisibility);
		ManaCost_SizeBox->SetVisibility(ManaVisibility);

		LevelImage->SetBrushFromTexture(Icons->LevelMap[level].CardTexture);
		
	}else if(NewCardPreset->CardType == ECardType::Effect)
	{
		Trap_SizeBox->SetVisibility(ESlateVisibility::Hidden);
		SetUnitVisibility(ESlateVisibility::Collapsed);

		ManaCost_SizeBox->SetVisibility(ESlateVisibility::HitTestInvisible);
		ManaCost->SetVisibility(ESlateVisibility::HitTestInvisible);
		Effect_SizeBox->SetVisibility(ESlateVisibility::Visible);

		Effect_Color1->SetBrushFromTexture(NewCardPreset->Texture1);
		Effect_Color2->SetBrushFromTexture(NewCardPreset->Texture2);
		
	}else
	{
		Effect_SizeBox->SetVisibility(ESlateVisibility::Hidden);
		SetUnitVisibility(ESlateVisibility::Hidden);
		ManaCost->SetVisibility(ESlateVisibility::HitTestInvisible);
		Trap_SizeBox->SetVisibility(ESlateVisibility::HitTestInvisible);
		Trap_Color1->SetBrushFromTexture(NewCardPreset->Texture1);
		Trap_Color2->SetBrushFromTexture(NewCardPreset->Texture2);
	}

	if(!bHasLevel)
	{
		Points->SetText(FText::AsNumber(NewCardPreset->Points));
		DescriptionText_RichText->SetText(NewCardPreset->CardDescription);
		ManaCost->SetText(FText::AsNumber(NewCardPreset->ManaCost));
	}else
	{
		const int LevelId = level-1;
		const auto PointsByLevel = UCardFunctionLibrary::GetPointsByLevel(NewCardPreset,num);
		const auto PointsText = FText::Format(FText::FromString("+{0}"),FText::AsNumber(PointsByLevel));
		Points->SetText(PointsText);
		DescriptionText_RichText->SetText(NewCardPreset->CardLevels[LevelId].CardDescription);
		ManaCost->SetText(FText::AsNumber(NewCardPreset->CardLevels[LevelId].ManaCost));
	}
}

void UCardWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	ColorPreset = NewColorPreset;
	const auto Color1 = NewColorPreset->GetColor(false,UseReserveColor,true);
	const auto Color2 = NewColorPreset->GetColor(true,UseReserveColor,true);
	UnitTypeBG->SetColorAndOpacity(Color1);
	Effect_BG->SetColorAndOpacity(Color1);
	Trap_BG->SetColorAndOpacity(Color1);
	Outline->SetColorAndOpacity(Color1);
	PointsBG->SetColorAndOpacity(Color1);
	Effect_Color2->SetColorAndOpacity(Color2);
	Trap_Color2->SetColorAndOpacity(Color2);
	Super::UpdateColor(NewColorPreset);
}

void UCardWidget::ActiveOutline(const bool Active)
{
	Outline->SetVisibility(Active ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void UCardWidget::PlayHighligh()
{
	PlayAnimation(Anim_Highlight);
}
