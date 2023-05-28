// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryWidget.h"
#include "MatchPlayerState.h"
#include <limits>

void UVictoryWidget::ShowScreen(const EPlayerVictoryState PlayerWinState, const AMatchPlayerState* Player,
                                const AMatchPlayerState* Opponent)
{
	GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(TakeWidget(),std::numeric_limits<int32>::max());
	StartAnimation(PlayerWinState,Player,Opponent);
}

void UVictoryWidget::RemoveScreen()
{
	GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(TakeWidget());
}
