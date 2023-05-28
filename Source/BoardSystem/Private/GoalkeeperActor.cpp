#include "GoalkeeperActor.h"

#include "BallMove.h"
#include "GoalkeeperPreset.h"
#include "Highlight.h"
#include "SetupSoccerActor.h"
#include "UserStatusStructs.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"


AGoalkeeperActor::AGoalkeeperActor() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
	GridWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GridWidgetComponent"));
	GridWidgetComponent->AttachToComponent(WidgetComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

void AGoalkeeperActor::InitDefaultMoves()
{
	for (auto MoveClass : BallMovesClasses)
	{
		const auto Move = NewObject<UBallMove>(this,MoveClass);
		Move->SetOwner(this);
		BallMoves.Add(Move);
	}
}

ABoardSlot* AGoalkeeperActor::GetCloserSlot(const FIntPoint Point)
{
	ABoardSlot* CloserSlot = NeighborSlots[0];
	int MinDistY = TNumericLimits<int>::Max();
	for (const auto Slot : NeighborSlots)
	{
		const int DistY = FMath::Abs(Point.Y - Slot->GridId.Y);
		if(FMath::Abs(Point.Y - Slot->GridId.Y) < MinDistY)
		{
			MinDistY = DistY;
			CloserSlot = Slot;
		} 
	}
	return CloserSlot;
}

void AGoalkeeperActor::TryMoveTo_Implementation(AActor* Target)
{
	return TryExecuteMove(Target);
}

UMove* AGoalkeeperActor::GetMove_Implementation(AActor* Target)
{
	return ActorValidMove(Target);
}

UGoalkeepersPreset* AGoalkeeperActor::GetPreset() const
{
	return GoalkepperPreset;
}

UColorPreset* AGoalkeeperActor::GetColor() const
{
	return ColorPreset;
}

void AGoalkeeperActor::SetData_Implementation(UGoalkeepersPreset* GoalkeeperPreset, UColorPreset* Color,bool UseReserve)
{
	ColorPreset = Color;
	GoalkepperPreset = GoalkeeperPreset;
	if(!WidgetComponent) return;
	UseReserveColor = UseReserve;
	OnSetup.Broadcast(this);

	const auto Widget = WidgetComponent->GetWidget();
	if(Widget->Implements<USetupSoccerActor>())
	{
		ISetupSoccerActor::Execute_Setup(Widget,this);
	}
}

void AGoalkeeperActor::SetNeighbors_Implementation(const TArray<ABoardSlot*>& Slots)
{
	NeighborSlots = Slots;
}

void AGoalkeeperActor::Hover_Implementation(EHoverType HoverType)
{
	IsHovered = true;
	OnSlotHovered.Broadcast();
	if(Highlight)
	{
		IHighlight::Execute_Hover(Highlight);
	}
}

int AGoalkeeperActor::GetOwnerPlayerId_Implementation()
{
	return OwnerPlayerId;
}

void AGoalkeeperActor::Unhover_Implementation()
{
	IsHovered = false;
	OnSlotUnhovered.Broadcast();
	if(Highlight)
	{
		IHighlight::Execute_Unhover(Highlight);
	}
}

void AGoalkeeperActor::Setup(UDataAsset* Preset, const FBoardPlayerData& PlayerData)
{
	GoalkepperPreset = Cast<UGoalkeepersPreset>(Preset);
	Super::Setup(Preset, PlayerData);
	SetData(GoalkepperPreset,PlayerData.PlayerStatus.ColorPalette,PlayerData.PlayerStatus.UseReserveColor);
}

void AGoalkeeperActor::ReceiveDamage(int OpponentPoints, ABallActor* OtherAttachedBall,AActor* DamageCauser,EDamageType DamageType)
{
	Super::ReceiveDamage(OpponentPoints,OtherAttachedBall,DamageCauser,DamageType);
	if(DamageType == EDamageType::Kick && !IsActivated())
	{
		ReceivedGoal = true;
	}
}

void AGoalkeeperActor::ResetPoints()
{
	ReceivedGoal = false;
	Super::ResetPoints();
}

void AGoalkeeperActor::Select_Implementation(const bool bValue)
{
	
}

bool AGoalkeeperActor::InteractionAllowed_Implementation(int Player)
{
	return false;
}

void AGoalkeeperActor::PossibleTarget_Implementation(bool value)
{
	OnPossibleSelection.Broadcast(value);
	if(Highlight)
	{
		IHighlight::Execute_Active(Highlight,value);
	}
}

void AGoalkeeperActor::BeginPlay()
{
	Super::BeginPlay();
	Highlight = GridWidgetComponent->GetWidget();
	if(HasAuthority())
	{
		InFormationState = false;
		SetPoints(DefaultPoints);
	}
}

void AGoalkeeperActor::SetLocation_Implementation(FVector Location, FRotator Rotator,bool Right)
{
	OnFlipVisual.Broadcast(Right);
	SetActorRotation(Rotator);
	SetActorLocation(Location);
	if(HasAuthority()) return;
	InvertLocation(Right);
}

void AGoalkeeperActor::InvertLocation(bool Right)
{
	const auto Location = GetActorLocation();
	const auto Local = GetActorRotation().RotateVector(Location);
	AddActorLocalOffset(FVector(0,Local.Y *-2,0));
	OnFlipVisual.Broadcast(!Right);
}

void AGoalkeeperActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGoalkeeperActor, NeighborSlots);
}

