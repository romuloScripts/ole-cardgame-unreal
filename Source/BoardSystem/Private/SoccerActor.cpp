#include "SoccerActor.h"

#include "WidgetComponentCustomCollision.h"
#include "Engine/ActorChannel.h"
#include "Move.h"
#include "BallMove.h"
#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "StatComponent.h"
#include "UserStatusStructs.h"
#include "CardSystem/Public/AbilityContainer.h"

class UBallMove;

ASoccerActor::ASoccerActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	BallTargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BallTarget"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponentCustomCollision>(TEXT("Widget"));
	SetRootComponent(SceneComponent);
	WidgetComponent->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);
	BallTargetComponent->AttachToComponent(WidgetComponent,FAttachmentTransformRules::KeepRelativeTransform);
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	StatComponent->SetIsReplicated(true);
}

APlayerState* ASoccerActor::GetOwnerPlayerState() const
{
	return OwnerPlayerState;
}

void ASoccerActor::MoveApplied_Implementation(EMoveType Move,AActor* Target)
{
	EMoveDirection Dir;
	const auto Vertical = Target->GetActorLocation().Y == GetActorLocation().Y;
	if(Vertical) Dir = Target->GetActorLocation().Z > GetActorLocation().Z ? EMoveDirection::Up : EMoveDirection::Down;
	else Dir = Target->GetActorLocation().Y > GetActorLocation().Y ? EMoveDirection::Left : EMoveDirection::Right;
	OnMoveApplied.Broadcast(Move,Dir);
}

void ASoccerActor::MoveReceived_Implementation(EMoveType Move,AActor* Causer, bool Success)
{
	const auto Dir = GetActorLocation().Y > Causer->GetActorLocation().Y ? EMoveDirection::Left : EMoveDirection::Right;
	OnMoveReceived.Broadcast(Move,Dir,Success);
}

bool ASoccerActor::SelectionAllowed(int PlayerId)
{
	return OwnerPlayerId == PlayerId;
}

void ASoccerActor::PostForceDamage_Implementation(int Damage)
{
	OnPostForceDamage.Broadcast(Damage);
}

void ASoccerActor::ReceivePointsEvent_Implementation(int Value)
{
	OnReceivePoints.Broadcast(Value);
}

void ASoccerActor::AddPoints_Implementation(int Value, bool AddToDefault)
{
	ReceivePointsEvent(Value);
	if(AddToDefault) DefaultPoints += Value;
	SetPoints(GetPoints()+Value);
}

void ASoccerActor::AddDefaultPoints_Implementation(int Value)
{
	DefaultPoints += Value;
}

void ASoccerActor::SetPoints(int NewPoints)
{
	Points = FMath::Max(0,NewPoints);
	WidgetUpdatePoints(Points);
	ActiveWidget(IsActivated());
}

void ASoccerActor::Setup_Implementation(UDataAsset* Preset, const FBoardPlayerData& State)
{
	SetOwnerPlayer(State.BoardIndex,State.PlayerState);
}

void ASoccerActor::SetOwnerPlayer_Implementation(int PlayerId, APlayerState* State)
{
	OwnerPlayerId = PlayerId;
	OwnerPlayerState = State;
	AbilityContainer = NewObject<UAbilityContainer>(this);
	AbilityContainer->Setup(OwnerPlayerState);
	AbilityContainer->OnChangeTrapEffect.AddDynamic(this,&ThisClass::ContainsTrapAbilityChanged);
}

void ASoccerActor::AttachBall(ABallActor* BallActor,ASoccerActor* OtherActor, bool bSetPos)
{
	if(BallActor == nullptr) return;
	BallActor->AttachedActor = this;
	if(bSetPos)
	{
		BallActor->SetActorLocation(BallTargetComponent->GetComponentLocation());
	}
	BallActor->AttachToComponent(BallTargetComponent,FAttachmentTransformRules::KeepWorldTransform);
	if(OtherActor) OnReceivePass.Broadcast(OtherActor);
}

void ASoccerActor::DamageOther(ASoccerActor* Target, const EDamageType DamageType, ABallActor* AttachedBall)
{
	if(DamageType != EDamageType::Kick)
	{
		//if(AttackedThisTurn) return;
		AttackedThisTurn = true;
	}
	
	Target->ReceiveDamage(GetPoints(),AttachedBall,this,DamageType);
}

void ASoccerActor::PostTakeDamageEvent_Implementation(EDamageType DamageType, int Damage,AActor* DamageCauser)
{
	OnPostTakeDamage.Broadcast(this,DamageType,Damage,DamageCauser);
}

void ASoccerActor::ReceiveDamage(int Damage, ABallActor* OtherAttachedBall,AActor* DamageCauser,EDamageType DamageType)
{
	OnBeforeTakeDamage.Broadcast(this,Damage,OtherAttachedBall != nullptr, DamageCauser);
	const auto Opponent = DamageCauser ? Cast<ASoccerActor>(DamageCauser) : nullptr;
	if(Opponent && !Opponent->IsActivated()) return;
	if(BlockDamage) return;
	SetPoints(GetPoints() - Damage);
	PostTakeDamageEvent(DamageType,Damage,DamageCauser);
}

void ASoccerActor::ForceDamage(const int Damage)
{
	SetPoints(GetPoints() - Damage);
	PostForceDamage(Damage);
}

UMove* ASoccerActor::ActorValidMove(AActor* Target)
{
	for (const auto Move : InFormationState ? FormationMoves : Moves)
	{
		if(Move->ValidTarget(Target))
		{
			return Move;
		}
	}
	return nullptr;
}

UMove* ASoccerActor::ActorValidBallMove(AActor* Target, ABallActor* Ball)
{
	if(Ball->AttachedActor != this) return nullptr;
	for (const auto Move : BallMoves)
	{
		if(Move->ValidTarget(Target))
		{
			return Move;
		}
	}
	return nullptr;
}

bool ASoccerActor::CanExecuteAnyMove() const
{
	for (const auto Move : BallMoves)
	{
		if(Move->HaveMana() && Move->InPossessOfBall())
		{
			return true;
		}
	}

	for (const auto Move : Moves)
	{
		if(Move->HaveMana())
		{
			return true;
		}
	}
	return false;
}

void ASoccerActor::TryExecuteBallMove_Implementation(AActor* Target, ABallActor* Ball)
{
	if(Ball->AttachedActor != this) return;
	for (const auto Move : BallMoves)
	{
		if(Move->Invoke(Target))
		{
			return;
		}
	}
}

bool ASoccerActor::IsActivated()
{
	return Points>0;
}

int ASoccerActor::GetPlayerId() const
{
	return OwnerPlayerId;
}

int ASoccerActor::GetPoints()
{
	return Points;
}

void ASoccerActor::SetBlockDamage(bool Block)
{
	BlockDamage = Block;
}

USceneComponent* ASoccerActor::GetBallTargetPoint()
{
	return BallTargetComponent;
}

void ASoccerActor::AddBallMove(TSubclassOf<UBallMove> MoveClass)
{
	const auto Move = NewObject<UBallMove>(this,MoveClass);
	Move->SetOwner(this);
	BallMoves.Add(Move);
}

void ASoccerActor::TryExecuteMove_Implementation(AActor* Target)
{
	for (const auto Move : InFormationState ? FormationMoves : Moves)
	{
		if(Move->Invoke(Target))
		{
			return;
		}
	}
}

void ASoccerActor::ResetPoints_Implementation()
{
	SetPoints(DefaultPoints);
	AttackedThisTurn = false;
	TArray<UMove*> AllMoves;
	AllMoves.Append(Moves);
	AllMoves.Append(BallMoves);
	for(const auto Move : AllMoves)
	{
		Move->ResetPoints();
	}
}

void ASoccerActor::ActiveWidget_Implementation(bool Value)
{
	OnChangeActive.Broadcast(Value);
}

void ASoccerActor::WidgetUpdatePoints_Implementation(int NewPoints)
{
	OnUpdatePoints.Broadcast(NewPoints);
}

void ASoccerActor::ContainsTrapAbilityChanged_Implementation(ETrapAbilityChange AbilityChange, UCard* Card)
{
	Trap = AbilityChange != ETrapAbilityChange::Remove;
	OnChangeTrapEffect.Broadcast(AbilityChange);
}

bool ASoccerActor::ContainsTrap() const
{
	return Trap;
}

bool ASoccerActor::GetAttackedThisTurn()
{
	return AttackedThisTurn;
}

void ASoccerActor::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority()) InitDefaultMoves();
}

void ASoccerActor::GetAllMovesOfType(const TSubclassOf<UMove> MoveClass, TArray<UMove*>& SelectedMoves)
{
	TArray<UMove*> AllMoves;
	AllMoves.Append(Moves);
	AllMoves.Append(BallMoves);
	for(const auto Move : AllMoves)
	{
		if(Move->IsA(MoveClass))
		{
			SelectedMoves.Add(Move);
		}
	}
}

void ASoccerActor::MoveBegin()
{
	const auto Board = UBoardFunctionLibrary::GetBoard(this);
	Board->MoveBegin(GetPlayerId());
}

void ASoccerActor::MoveEnd(UMove* Move) const
{
	OnAfterExecuteMove.Broadcast(Move);
	const auto Board = UBoardFunctionLibrary::GetBoard(this);
	Board->MoveEnd(GetPlayerId());
}

UCardPreset* ASoccerActor::GetTrapCard()
{
	if(!AbilityContainer) return nullptr;
	return AbilityContainer->GetTrapCard();
}

bool ASoccerActor::IsLocal() const
{
	if(GetOwner() != nullptr)
	{
		const auto Player = Cast<APlayerController>(GetOwner());
		return Player && Player->IsLocalPlayerController();
	}
	return false;
}

APlayerController* ASoccerActor::GetOwnerPlayerController() const
{
	const auto Player = Cast<APlayerController>(GetOwner());
	return Player;
}

void ASoccerActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASoccerActor, OwnerPlayerId);
	DOREPLIFETIME(ASoccerActor, OwnerPlayerState);
	DOREPLIFETIME(ASoccerActor, Points);
	DOREPLIFETIME(ASoccerActor, InFormationState);
	DOREPLIFETIME(ASoccerActor, DefaultPoints);
	DOREPLIFETIME(ASoccerActor, Moves);
	DOREPLIFETIME(ASoccerActor, BallMoves);
	DOREPLIFETIME(ASoccerActor, FormationMoves);
	DOREPLIFETIME(ASoccerActor, AttackedThisTurn);
}

void ASoccerActor::CanReplicateArray(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags,
	bool& WroteSomething, const TArray<UMove*> Array)
{
	for (auto& Item : Array)
	{
		WroteSomething |= Channel->ReplicateSubobject(Item, *Bunch, *RepFlags);
	}
}

bool ASoccerActor::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, BallMoves);
	if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, Moves);
	if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, FormationMoves);
	if(WroteSomething) return true;
	return WroteSomething;
}
