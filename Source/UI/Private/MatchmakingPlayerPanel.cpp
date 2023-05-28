// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchmakingPlayerPanel.h"

#include "DeckFunctionLibrary.h"
#include "UnitWidget.h"
#include "IconsPreset.h"
#include "WidgetFunctionLibrary.h"

void UMatchmakingPlayerPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateUser(User,false);
}

void UMatchmakingPlayerPanel::UpdateUser(const FPlayerStatus UserStatus,bool ReserveColor)
{
	User = UserStatus;
	const auto ColorPreset = UserStatus.ColorPalette;
	
	if(ColorPreset)
		PlayerColor->SetColorAndOpacity(ColorPreset->Color1);
	Username->SetText(FText::FromName(UserStatus.UserName));
	Level->SetText(UWidgetFunctionLibrary::GetLevelText(UserStatus.Level));
	if(ColorPreset)
		Level->SetColorAndOpacity(ColorPreset->Color2);

	auto Deck = UserStatus.Deck;
	int NumCards = Deck.Cards.Num();
	if(Icons)
		Class->SetBrushFromTexture(Icons->ClassMap[Deck.CardClass].IconTexture);
	Emblem->UpdateEmblem(UserStatus.Emblem);
	Emblem->UpdateColor(UserStatus.ColorPalette);

	for (auto UnitWidget : UnitArray)
	{
		UnitWidget->RemoveFromParent();
	}
	UnitArray.Empty();
	
	if (NumCards == 0 || Unit == nullptr)
	{
		return;
	}

	auto Cards = UDeckFunctionLibrary::GetUnitsCardsFromDeck(Deck);
	int Index =0;
	
	for (auto Card : Cards)
	{
		if(Index >= UnitPanel->GetChildrenCount()) break;
		UUnitWidget* UnitInstance = CreateWidget<UUnitWidget>(this, Unit);
		UnitArray.Add(UnitInstance);

		const auto PanelChild = Cast<USizeBox>(UnitPanel->GetChildAt(Index));
		Index++;
		if(!PanelChild) continue;
		
		USizeBoxSlot* slot = Cast<USizeBoxSlot>(PanelChild->AddChild(UnitInstance));
		slot->SetHorizontalAlignment(HAlign_Fill);
		slot->SetVerticalAlignment(VAlign_Fill);
		UnitInstance->UpdateUnit(Card);
		UnitInstance->UpdateUniform(UserStatus.Uniform);
		UnitInstance->UpdateColorAndReserve(ColorPreset,ReserveColor);
	}
}

void UMatchmakingPlayerPanel::PlayAnimEmblem()
{
	PlayAnimation(AnimEmblem);
}

void UMatchmakingPlayerPanel::PlayAnimTeam()
{
	UnitPanel->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(RightSide ? AnimTeamRight : AnimTeamLeft);
}

void UMatchmakingPlayerPanel::PlayTransition()
{
	PlayAnimation(RightSide ? AnimTransitionRight : AnimTransitionLeft);
}
