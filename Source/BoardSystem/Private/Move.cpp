#include "Move.h"

#include "Net/UnrealNetwork.h"
#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"
#include "ContainsMana.h"
#include "SoccerActor.h"
#include "GameFramework/PlayerState.h"

void UMove::SetOwner(ASoccerActor* Target)
{
	OwnerActor = Target;
	CurrentManaCost = ManaCost;
	PostSetOwner(Target);
}

FText UMove::GetActionInfo()
{
	return ActionInfo;
}

bool UMove::Allowed(AActor* Target)
{
	return InteractionAllowed(Target);
}

void UMove::PostSetOwner(ASoccerActor* Target)
{
}

bool UMove::InteractionAllowed(AActor* Target)
{
	return ValidTarget(Target);
}

bool UMove::Invoke(AActor* Target)
{
	if(!Allowed(Target)) return false;
	const auto OwnerPlayerState = OwnerActor->GetOwnerPlayerState();
	if(OwnerPlayerState->Implements<UContainsMana>())
	{
		IContainsMana::Execute_ConsumeMana(OwnerPlayerState, CurrentManaCost);
	}
	OwnerActor->MoveBegin();
	Move(Target);
	return true;
}

void UMove::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UMove, OwnerActor);
	DOREPLIFETIME(UMove, CurrentManaCost);
}

void UMove::ResetPoints()
{
}

void UMove::Move(AActor* Target)
{
	
}

bool UMove::ValidTarget(AActor* Target)
{
	return HaveMana() ? TargetIsValid(Target) : false;
}

bool UMove::TargetIsValid(AActor* Target)
{
	if(Target == nullptr) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(TargetSlot && TargetSlot->AttachedUnit == OwnerActor) return false;
	return Target != OwnerActor;
}

void UMove::EndMove()
{
	OwnerActor->MoveEnd(this);
}

bool UMove::HaveMana() const
{
	const auto OwnerPlayerState = OwnerActor->GetOwnerPlayerState();
	if(OwnerPlayerState && OwnerPlayerState->Implements<UContainsMana>())
	{
		return IContainsMana::Execute_GetMana(OwnerPlayerState) >= CurrentManaCost;
	}
	return false;
}

bool UMove::InPossessOfBall() const
{
	return UBoardFunctionLibrary::BallInPossesOfActor(OwnerActor);
}
