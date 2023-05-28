// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

#include "MatchGameState.h"


void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameState = Cast<AMatchGameState>(GetWorld()->GetGameState());
}
