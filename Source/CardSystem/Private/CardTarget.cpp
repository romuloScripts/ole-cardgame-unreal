// Fill out your copyright notice in the Description page of Project Settings.


#include "CardTarget.h"
#include "Net/UnrealNetwork.h"
#include "Card.h"

void UCardTarget::Setup(UCard* OwnerCard)
{
	Card = OwnerCard;
}

void UCardTarget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCardTarget, Card);
}

TArray<FCardDropTargetInfo> UCardTarget::GetTargets()
{
	return RequestTargets();
}

UCard* UCardTarget::GetCard() const
{
	return Card;
}

APlayerState* UCardTarget::GetPlayer() const
{
	return Card->GetOwnerPlayer();
}

TArray<FCardDropTargetInfo> UCardTarget::RequestTargets_Implementation()
{
	TArray<FCardDropTargetInfo> Targets;
	return Targets;
}
