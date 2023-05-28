
#include "BallActor.h"
#include "Move.h"
#include "SetupBallActor.h"
#include "SoccerActor.h"
#include "Net/UnrealNetwork.h"


ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	SetRootComponent(WidgetComponent);
}

void ABallActor::AttachToSoccerActorLocal(ASoccerActor* SoccerActor, bool SetPos)
{
	const auto OtherActor = TargetActor == SoccerActor && AttachedActor ? AttachedActor : nullptr;
	SoccerActor->AttachBall(this,OtherActor,SetPos);
}

void ABallActor::AttachToSoccerActor_Implementation(ASoccerActor* SoccerActor, bool SetPos)
{
	AttachToSoccerActorLocal(SoccerActor, SetPos);
}

void ABallActor::MoveToActor_Implementation(ASoccerActor* SoccerActor)
{
	TargetActor = SoccerActor;
	StartMovementAnimation();
}

void ABallActor::Select_Implementation(const bool Value)
{
	if(Value) OnHover.Broadcast(true);
	else OnHover.Broadcast(false);
} 

void ABallActor::Hover_Implementation(EHoverType HoverType)
{
	OnHover.Broadcast(true);
}

void ABallActor::Unhover_Implementation()
{
	OnHover.Broadcast(false);
}

int ABallActor::GetOwnerPlayerId_Implementation()
{
	if(!AttachedActor) return -1;
	return AttachedActor->GetPlayerId();
}

bool ABallActor::InteractionAllowed_Implementation(int PlayerId)
{
	if(AttachedActor)
	{
		return  AttachedActor->SelectionAllowed(PlayerId);
	}
	return false;
}

void ABallActor::TryMoveTo_Implementation(AActor* Target)
{
	if(AttachedActor == nullptr) return;
	AttachedActor->TryExecuteBallMove(Target,this);
}

UMove* ABallActor::GetMove_Implementation(AActor* Target)
{
	if(AttachedActor == nullptr) return nullptr;
	return AttachedActor->ActorValidBallMove(Target,this);
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

void ABallActor::StartMovementAnimation()
{
	LastPos = GetActorLocation();
	if (MovementAnimCurve)
	{
		Timeline.PlayFromStart();
	}
}

void ABallActor::SetMovementAnimValue(float Value)
{
	const FVector Pos = TargetActor->GetBallTargetPoint()->GetComponentLocation();
	const auto Result = FMath::Lerp(LastPos,Pos,Value);
	SetActorLocation(Result);
}

void ABallActor::EndMovementAnimation()
{
	AttachToSoccerActorLocal(TargetActor,true);
	TargetActor = nullptr;
	const auto Event =  OnAnimFinished;
	OnAnimFinished.Clear();
	Event.Broadcast();
}

void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	const auto Widget = WidgetComponent->GetWidget();
	if(Widget && Widget->Implements<USetupBallActor>())
	{
		ISetupBallActor::Execute_Setup(Widget,this);
	} 
	if (MovementAnimCurve)
	{
		FOnTimelineFloat SetValue;
		FOnTimelineEventStatic TimelineFinishedCallback;

		SetValue.BindUFunction(this, FName("SetMovementAnimValue"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("EndMovementAnimation") });
		Timeline.AddInterpFloat(MovementAnimCurve, SetValue);
		Timeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABallActor, AttachedActor);
}

