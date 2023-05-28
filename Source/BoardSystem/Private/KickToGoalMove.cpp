#include "KickToGoalMove.h"

#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "GoalkeeperActor.h"
#include "StatComponent.h"
#include "GameTags.h"
#include "Net/UnrealNetwork.h"

bool UKickToGoalMove::InteractionAllowed(AActor* Target)
{
	if(!Super::InteractionAllowed(Target)) return false;
	const auto GoalkeeperTarget = Cast<AGoalkeeperActor>(Target);
	bool OpponentsInFront;
	return !ReachedMaxKicks() && UBoardFunctionLibrary::IsKickAllowed(GoalkeeperTarget,1,OpponentsInFront);
}

void UKickToGoalMove::ResetPoints()
{
	Super::ResetPoints();
	NumKicks = 0;
}

void UKickToGoalMove::Move(AActor* Target)
{
	Goalkeeper = Cast<AGoalkeeperActor>(Target);
	const auto Ball = UBoardFunctionLibrary::GetBall(GetWorld());
	OwnerActor->MoveApplied(EMoveType::Kick,Goalkeeper);
	Ball->OnAnimFinished.AddDynamic(this,&UKickToGoalMove::BallReached);
	Ball->MoveToActor(Goalkeeper);
}

void UKickToGoalMove::BallReached()
{
	const auto Ball = UBoardFunctionLibrary::GetBall(GetWorld());
	OwnerActor->DamageOther(Goalkeeper,EDamageType::Kick,Ball);
	NumKicks++;
	if(Goalkeeper->IsActivated())
	{
		if(ReachedMaxKicks())
		{
			EndMove();
		}else
		{
			const auto Points = OwnerActor->GetPoints();
			OwnerActor->SetPoints(Points > 1 ? Points/2 : 1);
			Ball->OnAnimFinished.AddDynamic(this,&UKickToGoalMove::BallReturned);
			Ball->MoveToActor(OwnerActor);
		}
	}else
	{
		const auto Board = UBoardFunctionLibrary::GetBoard(this);
		Board->Goal(OwnerActor->GetPlayerId());
		EndMove();
	}
}

void UKickToGoalMove::BallReturned()
{
	EndMove();
}

bool UKickToGoalMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target)) return false;
	const auto GoalkeeperTarget = Cast<AGoalkeeperActor>(Target);
	bool OpponentsInFront;
	const bool KickAllowed = UBoardFunctionLibrary::IsKickAllowed(GoalkeeperTarget,1,OpponentsInFront);
	return GoalkeeperTarget && (KickAllowed || OpponentsInFront);
}

void UKickToGoalMove::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UKickToGoalMove, NumKicks);
}

int UKickToGoalMove::GetMaxKicks() const
{
	const auto Stats = UBoardFunctionLibrary::GetStatComponent(OwnerActor);
	return Stats->ContainsStat(TAG_Stat_Rebound) ? MaxKicks + 1 : MaxKicks;
}

bool UKickToGoalMove::ReachedMaxKicks() const
{
	return NumKicks >= GetMaxKicks();
}
