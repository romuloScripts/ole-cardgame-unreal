// Fill out your copyright notice in the Description page of Project Settings.


#include "DribbleMove.h"
#include "BoardSlot.h"
#include "BoardFunctionLibrary.h"

bool UDribbleMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target) || UnitActor->GetAttackedThisTurn()) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(TargetSlot == nullptr) return false;
	const auto Opponent = TargetSlot->AttachedUnit;
	const auto BallActor = UBoardFunctionLibrary::GetBall(GetWorld())->AttachedActor;
	return UBoardFunctionLibrary::OpponentOnSide(UnitActor,Opponent) && BallActor == UnitActor;
}

void UDribbleMove::Move(AActor* Target)
{
	BeginAttack(Target,EMoveType::Dribble,EDamageType::Dribble,EMoveType::Dribbled);
}
