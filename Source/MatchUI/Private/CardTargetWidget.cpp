// Fill out your copyright notice in the Description page of Project Settings.


#include "CardTargetWidget.h"

void UCardTargetWidget::Setup(AMatchPlayerState* Player,UCardSelectTarget* CardSelectTarget)
{
	PlayerState = Player;
	ShowTargets();
}

void UCardTargetWidget::ShowTargets_Implementation()
{
}
