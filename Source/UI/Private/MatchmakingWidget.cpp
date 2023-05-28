// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchmakingWidget.h"

void UMatchmakingWidget::SetPlayer(FPlayerStatus PlayerStatus)
{
	PlayerPanel->UpdateUser(PlayerStatus,PlayerStatus.UseReserveColor);
}

void UMatchmakingWidget::SetOpponent(FPlayerStatus OpponentStatus)
{
	OpponentPanel->UpdateUser(OpponentStatus,OpponentStatus.UseReserveColor);
}
