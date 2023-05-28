// Fill out your copyright notice in the Description page of Project Settings.


#include "PassBallMove.h"

#include "BoardSlot.h"
#include "BoardFunctionLibrary.h"

bool UPassBallMove::InteractionAllowed(AActor* Target)
{
	if(!Super::InteractionAllowed(Target)) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	bool OpponentInFront;
	return UBoardFunctionLibrary::IsPassAllowed(TargetSlot,MaxDistance,OpponentInFront);
}

void UPassBallMove::Move(AActor* Target)
{
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	const auto Ball = UBoardFunctionLibrary::GetBall(GetWorld());
	Ball->OnAnimFinished.AddDynamic(this,&UPassBallMove::EndMove);
	OwnerActor->MoveApplied(EMoveType::Pass,TargetSlot);
	Ball->MoveToActor(TargetSlot->AttachedUnit);
}

bool UPassBallMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target))  return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(!TargetSlot || !TargetSlot->AttachedUnit || TargetSlot->PlayerId != OwnerActor->GetPlayerId()) return false;
	bool OpponentInFront;
	const bool PassAllowed = UBoardFunctionLibrary::IsPassAllowed(TargetSlot,MaxDistance,OpponentInFront);
	return PassAllowed || OpponentInFront;
}
