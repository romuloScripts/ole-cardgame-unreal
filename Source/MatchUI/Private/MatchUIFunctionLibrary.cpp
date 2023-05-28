// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchUIFunctionLibrary.h"
#include "MatchHUD.h"
#include "MatchPlayerController.h"
#include "Kismet/GameplayStatics.h"


UHudWidget* UMatchUIFunctionLibrary::GetHudWidget(UObject* Instigator)
{
	const auto Player = Cast<AMatchPlayerController>(UGameplayStatics::GetPlayerController(Instigator,0));
	if(!Player) return nullptr;
	return Cast<UMatchHUD>(Player->GetMatchHud())->HudWidget;
}

UMatchHUD* UMatchUIFunctionLibrary::GetPlayerHud(UObject* Instigator)
{
	const auto Player = Cast<AMatchPlayerController>(UGameplayStatics::GetPlayerController(Instigator,0));
	if(!Player) return nullptr;
	return Cast<UMatchHUD>(Player->GetMatchHud());
}
