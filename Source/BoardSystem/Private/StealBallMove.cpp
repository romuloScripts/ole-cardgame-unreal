// Fill out your copyright notice in the Description page of Project Settings.


#include "StealBallMove.h"

#include "BoardSlot.h"
#include "BoardFunctionLibrary.h"

bool UStealBallMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target) || UnitActor->GetAttackedThisTurn()) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(TargetSlot == nullptr) return false;
	const auto Opponent = TargetSlot->AttachedUnit;
	const auto BallUnit = UBoardFunctionLibrary::GetBall(GetWorld())->AttachedActor;
	return UBoardFunctionLibrary::OpponentOnSide(UnitActor,Opponent,false) && BallUnit == Opponent;
}

void UStealBallMove::EndAttack()
{
	DoubleAttack();
	if(!OpponentUnit->IsActivated())
	{
		const auto Ball = UBoardFunctionLibrary::GetBall(GetWorld());
		Ball->AttachToSoccerActor(UnitActor,true);
	}
	EndMove();
}

void UStealBallMove::Move(AActor* Target)
{
	BeginAttack(Target,EMoveType::Dribble,EDamageType::StealBall,EMoveType::Dribbled);
}
