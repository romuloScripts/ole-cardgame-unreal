// Fill out your copyright notice in the Description page of Project Settings.
#include "TurnButtonWidget.h"
#include "MatchGameState.h"
#include "Components/Button.h"

void UTurnButtonWidget::UpdateTime_Implementation(float Time, float Duration)
{
}

void UTurnButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Button->OnClicked.AddDynamic(this,&ThisClass::OnClick);
}

void UTurnButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameState = Cast<AMatchGameState>(GetWorld()->GetGameState());
}

void UTurnButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(GameState == nullptr) return;
	UpdateTime(GameState->TurnTime,GameState->TurnMaxTime);
}

void UTurnButtonWidget::OnClick()
{
	OnClicked.Broadcast();
}

void UTurnButtonWidget::ActiveButton(const ESlateVisibility ESlateVisibility) const
{
	Button->SetVisibility(ESlateVisibility);
}
