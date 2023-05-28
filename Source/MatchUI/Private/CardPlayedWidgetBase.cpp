// Fill out your copyright notice in the Description page of Project Settings.

#include "CardPlayedWidgetBase.h"

#include "CardBackContainer.h"
#include "CardWidget.h"
#include "MatchPlayerState.h"

void UCardPlayedWidgetBase::SetUser(AMatchPlayerState* Player, bool IsOpponent)
{
	PlayerState = Player;
	UserStatus = PlayerState->PlayerStatus;
	UpdateVisual();
	PostSetUser();
}

void UCardPlayedWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	if(IsDesignTime()) UpdateVisual();
}

void UCardPlayedWidgetBase::UpdateVisual()
{
	if(GradientBG && UserStatus.ColorPalette) GradientBG->SetColorAndOpacity(UserStatus.ColorPalette->Color1);
	if(CardBack)
	{
		CardBack->UpdateColorAndReserve(UserStatus.ColorPalette,UserStatus.UseReserveColor);
		CardBack->UpdateCardBack(UserStatus.CardBack);
	} 
	if(Card)
	{
		Card->UpdateColorAndReserve(UserStatus.ColorPalette,UserStatus.UseReserveColor);
		Card->UpdateUniform(UserStatus.Uniform);
	}
	PostUpdateVisual();
}
