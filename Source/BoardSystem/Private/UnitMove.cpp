// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitMove.h"

#include "UnitActor.h"
#include "Net/UnrealNetwork.h"

void UUnitMove::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UUnitMove, UnitActor);
}

bool UUnitMove::TargetIsValid(AActor* Target)
{
	return Super::TargetIsValid(Target) && UnitActor && UnitActor->CurrentSlot;
}

void UUnitMove::PostSetOwner(ASoccerActor* Target)
{
	UnitActor = Cast<AUnitActor>(Target);
}
