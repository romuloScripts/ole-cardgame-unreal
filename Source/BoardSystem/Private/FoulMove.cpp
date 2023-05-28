#include "FoulMove.h"

#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"

bool UFoulMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target) || UnitActor->GetAttackedThisTurn()) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(TargetSlot == nullptr) return false;
	const auto Opponent = TargetSlot->AttachedUnit;
	const auto BallUnit = UBoardFunctionLibrary::GetBall(GetWorld())->AttachedActor;
	return UBoardFunctionLibrary::OpponentOnSide(UnitActor,Opponent) && BallUnit != Opponent && BallUnit != UnitActor;
}

void UFoulMove::EndAttack()
{
	DoubleAttack();
	UnitActor->AddYellowCard();
	EndMove();
}

void UFoulMove::Move(AActor* Target)
{
	BeginAttack(Target,EMoveType::Dribble,EDamageType::Foul,EMoveType::Dribble);
}
