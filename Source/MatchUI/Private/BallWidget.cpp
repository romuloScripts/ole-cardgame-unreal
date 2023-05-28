// Fill out your copyright notice in the Description page of Project Settings.


#include "BallWidget.h"
#include "BallActor.h"

void UBallWidget::Setup_Implementation(ABallActor* BallActor)
{
	BallActor->OnHover.AddDynamic(this,&ThisClass::HoverEvent);
}

void UBallWidget::ActiveInteraction(bool Value)
{
	if(!Value) Unhover();
}

void UBallWidget::HoverEvent(bool Value)
{
	if(Value) Hover();
	else Unhover();
}
