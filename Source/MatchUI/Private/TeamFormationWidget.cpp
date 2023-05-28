// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamFormationWidget.h"
#include "MatchPlayerState.h"

void UTeamFormationWidget::SetUser(AMatchPlayerController* PlayerController, AMatchPlayerState* PlayerState)
{
	OwnerPlayerController = PlayerController;
	UpdateColor(PlayerState->PlayerStatus.ColorPalette);
}
