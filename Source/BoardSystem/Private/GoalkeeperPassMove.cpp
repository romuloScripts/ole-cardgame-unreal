#include "GoalkeeperPassMove.h"

#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"
#include "BallActor.h"

void UGoalkeeperPassMove::Move(AActor* Target)
{
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	const auto Ball = UBoardFunctionLibrary::GetBall(GetWorld());
	Ball->OnAnimFinished.AddDynamic(this,&UGoalkeeperPassMove::EndMove);
	Ball->MoveToActor(TargetSlot->AttachedUnit);
}

bool UGoalkeeperPassMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target)) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(!TargetSlot || !TargetSlot->AttachedUnit || TargetSlot->PlayerId != OwnerActor->GetPlayerId()) return false;
	const auto Type = TargetSlot->CardType;
	return Type == TargetType;
}
