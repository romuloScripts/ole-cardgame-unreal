// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "MatchGameState.h"
#include "Components/TextBlock.h"

void UTimerWidget::UpdateTimer()
{
	const int Turn = GameState->TotalTurns;
	const int MaxTurns = GameState->MaxTurns;
	const int MinutesPerTurn = MatchMaxMinutes/MaxTurns;
	const int MinutesPerHalf = MatchMaxMinutes/NumHalves;
	const int Minutes = Turn >= MaxTurns ? MinutesPerHalf : (MinutesPerTurn * Turn)%MinutesPerHalf;
	const int Half = FMath::Clamp( Turn / (MaxTurns/NumHalves) + 1 , 1 , NumHalves);
	MatchTimeText->SetText(FText::Format(FText::FromString(TEXT("{0}º")), FText::AsNumber(Half)));
	MinuteText->SetText(FText::Format(FText::FromString("{0}'"), FText::AsNumber(Minutes)));
}

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameState = Cast<AMatchGameState>(GetWorld()->GetGameState());
	GameState->OnTurnChanged.AddDynamic(this,&ThisClass::UpdateTimer);
}
