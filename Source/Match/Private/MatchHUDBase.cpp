// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchHUDBase.h"
#include "UserStatusStructs.h"
#include "Net/UnrealNetwork.h"

UMatchHUDBase::UMatchHUDBase()
{
	SetIsReplicated(true);
}

bool UMatchHUDBase::ShowCardPreview(UCardPreset* Card, const FPlayerStatus& PlayerStatus)
{
	return false;
}

FVector UMatchHUDBase::GetCardWidgetArrowOriginPos()
{
	return FVector::Zero();
}

void UMatchHUDBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UMatchHUDBase, CoinFlipEnded);
	DOREPLIFETIME(UMatchHUDBase, MulliganEnded);
	DOREPLIFETIME(UMatchHUDBase, GoalScreenEnded);
}

void UMatchHUDBase::ShowFlipCoinScreen_Implementation(bool First)
{
}

void UMatchHUDBase::CoinFlipFinished()
{
}

void UMatchHUDBase::CoinFlipFinishedServer_Implementation()
{
}

void UMatchHUDBase::ShowMulliganCards_Implementation(const TArray<UCardPreset*>& DeckHolderCards)
{
}

void UMatchHUDBase::GetMulliganReplaceCards_Implementation()
{
}

void UMatchHUDBase::GoalScreen_Implementation(int PlayerId)
{
}

void UMatchHUDBase::GoalScreenFinished_Implementation()
{
}

void UMatchHUDBase::ShowTeamFormation_Implementation()
{
}

void UMatchHUDBase::RemoveTeamFormation_Implementation()
{
}

void UMatchHUDBase::ShowVictory_Implementation(const EPlayerVictoryState& VictoryState)
{
}

void UMatchHUDBase::CreateHud_Implementation(AMatchPlayerState* Opponent)
{
}

void UMatchHUDBase::ShowRedCardMessage_Implementation(UCardPreset* CardPreset, bool Opponent)
{
}



