// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSwitcherParams.h"

void UMenuSwitcherParams::ChangeMenuTab()
{
	// if(GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("change menu")));
	Menu_WidgetSwitcher->SetActiveWidgetIndex(menuIndex);
}
