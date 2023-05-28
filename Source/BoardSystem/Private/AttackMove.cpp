// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackMove.h"
#include "StatComponent.h"
#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"
#include "UnitActor.h"
#include "GameTags.h"

void UAttackMove::BeginAttack(AActor* Target,EMoveType MoveType,EDamageType DamageType,EMoveType MoveReceived)
{
	Attack(Target, MoveType, DamageType, MoveReceived);
	GetWorld()->GetTimerManager().SetTimer(DelayAttackTimer, this, &ThisClass::EndAttack, 0.2f, false);
}

void UAttackMove::DoubleAttack()
{
	const auto StatComponent = UBoardFunctionLibrary::GetStatComponent(UnitActor);
	if(OpponentUnit->IsActivated() && StatComponent && StatComponent->GetStats().HasTag(TAG_Stat_DoubleAttack))
	{
		Attack(OpponentUnit,EMoveType::Dribble,EDamageType::Dribble,EMoveType::Dribbled);
	}
}

void UAttackMove::EndAttack()
{
	DoubleAttack();
	EndMove();
}

void UAttackMove::Attack(AActor* Target, EMoveType MoveType, EDamageType DamageType, EMoveType MoveReceived)
{
	const auto Slot = Cast<ABoardSlot>(Target);
	if(Slot) OpponentUnit = Slot->AttachedUnit;
	else OpponentUnit = Cast<AUnitActor>(Target);
	OwnerActor->MoveApplied(MoveType,OpponentUnit);
	UnitActor->DamageOther(OpponentUnit,DamageType,nullptr);
	const bool Success = !OpponentUnit->IsActivated();
	OpponentUnit->MoveReceived(MoveReceived,UnitActor,Success);
}
