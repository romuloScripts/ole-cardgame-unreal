// Fill out your copyright notice in the Description page of Project Settings.


#include "MulliganCardWidget.h"

void UMulliganCardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMulliganCardWidget::CardClicked()
{
	OnCardClicked.Broadcast(this);
}
