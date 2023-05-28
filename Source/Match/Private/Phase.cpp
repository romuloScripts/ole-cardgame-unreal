// Fill out your copyright notice in the Description page of Project Settings.


#include "Phase.h"

void UPhase::OnBegin(const FGameContext& Context)
{
	GameContext = Context;
}

void UPhase::OnEnd()
{
}

void UPhase::UpdatePhase(float Delta)
{
}

TSubclassOf<UPhase> UPhase::GetNextPhase()
{
	return NextPhase;
}

bool UPhase::EndIf()
{
	return false;
}
