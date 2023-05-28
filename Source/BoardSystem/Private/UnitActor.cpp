

#include "UnitActor.h"
#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"
#include "CardFunctionLibrary.h"
#include "CardPreset.h"
#include "UnitMove.h"
#include "UserStatusStructs.h"
#include "WidgetComponentCustomCollision.h"
#include "AbilityContainer.h"
#include "CardDropTargetInfo.h"
#include "CardSystemFunctionLibrary.h"
#include "SetupSoccerActor.h"
#include "Net/UnrealNetwork.h"

AUnitActor::AUnitActor() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitActor::InitAbilities()
{
	FCardDropTargetInfo DropTargetInfo;
	DropTargetInfo.AbilityContainer = AbilityContainer;
	DropTargetInfo.DropTarget = this;
	for (const auto Ability : UCardSystemFunctionLibrary::GetAbilityByLevel(CardPreset,Level))
	{
		UCardSystemFunctionLibrary::CreateAbility(DropTargetInfo,Ability);
	}
}

void AUnitActor::AddYellowCard()
{
	if(YellowCard)
	{
		SetRedCard();
	}else
	{
		YellowCard = true;
		OnRep_OnYellowCardChanged();
	}
}

bool AUnitActor::GetYellowCard() const
{
	return YellowCard;
}

void AUnitActor::SetRedCard()
{
	RedCard = true;
	AbilityContainer->RemoveAllEffects();
	OnRedCardReceived.Broadcast(this);
	if(CurrentSlot) CurrentSlot->AttachUnit(nullptr);
	Destroy();
}

bool AUnitActor::GetRedCard() const
{
	return RedCard;
}

bool AUnitActor::IsInMaxLevel() const
{
	return Level >= CardPreset->CardLevels.Num() + 1;
}

void AUnitActor::InitDefaultMoves()
{
	for (auto MoveClass : FormationMovesClasses)
	{
		const auto Move = NewObject<UUnitMove>(this,MoveClass);
		Move->SetOwner(this);
		FormationMoves.Add(Move);
	}
	
	for (auto MoveClass : MovesClasses)
	{
		const auto Move = NewObject<UUnitMove>(this,MoveClass);
		Move->SetOwner(this);
		Moves.Add(Move);
	}

	for (const auto MoveClass : BallMovesClasses)
	{
		AddBallMove(MoveClass);
	}
}

void AUnitActor::BeginPlay()
{
	Super::BeginPlay();
	if (MovementAnimCurve)
	{
		FOnTimelineFloat SetValue;
		FOnTimelineEventStatic TimelineFinishedCallback;

		SetValue.BindUFunction(this, FName("SetMovementAnimValue"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("EndMovementAnimation") });
		Timeline.AddInterpFloat(MovementAnimCurve, SetValue);
		Timeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}

	if(!IsLocal())
	{
		InvertBallLocation();
	}
}

void AUnitActor::Setup(UDataAsset* Preset, const FBoardPlayerData& PlayerData)
{
	CardPreset = Cast<UCardPreset>(Preset);
	Super::Setup(Preset, PlayerData);
	SetCard(CardPreset,PlayerData.PlayerStatus.Uniform,PlayerData.PlayerStatus.ColorPalette,PlayerData.PlayerStatus.UseReserveColor);
}

void AUnitActor::SetOwnerPlayer(int PlayerId, APlayerState* State)
{
	Super::SetOwnerPlayer(PlayerId, State);
	InitAbilities();
}

void AUnitActor::InvertBallLocation() const
{
	const auto Location = BallTargetComponent->GetRelativeLocation();
	BallTargetComponent->SetRelativeLocation(FVector(Location.X,Location.Y *-1,Location.Z));
}

void AUnitActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUnitActor, CurrentSlot);
	DOREPLIFETIME(AUnitActor, YellowCard);
	DOREPLIFETIME(AUnitActor, RedCard);
	DOREPLIFETIME(AUnitActor, Level);
}

void AUnitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

void AUnitActor::AttachToSlotAndTeleport_Implementation(ABoardSlot* Slot)
{
	AttachToSlot(Slot);
	ToSlot(Slot);
}

void AUnitActor::MoveToSlot_Implementation(ABoardSlot* Slot)
{
	CurrentSlot = Slot;
	StartMovementAnimation();
}

void AUnitActor::ToSlot_Implementation(ABoardSlot* Slot)
{
	SetActorLocation(Slot->GetActorLocation());
	SetActorRotation(Slot->GetActorRotation());
}

void AUnitActor::ActiveVisibility_Implementation()
{
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void AUnitActor::LevelUp()
{
	const auto NextLevel = UBoardFunctionLibrary::GetUnitNextLevel(this);
	const auto NextLevelPoints = UCardFunctionLibrary::GetPointsByLevel(CardPreset,NextLevel);
	AddPoints(NextLevelPoints,true);
	Level = NextLevel;
	OnRep_OnLevelChanged();
}

void AUnitActor::OnRep_OnLevelChanged() const
{
	OnLevelUp.Broadcast(Level);
}

void AUnitActor::OnRep_OnYellowCardChanged() const
{
	OnChangeYellowCard.Broadcast(YellowCard);
}

void AUnitActor::Selected(bool Value)
{
	if(Value)
	{
		Hover(EHoverType::Select);
	}
	else
	{
		Unhover();
	}
}

void AUnitActor::WidgetUpdatePoints_Implementation(int Point)
{
	OnPointsChanged.Broadcast(Point);
}

void AUnitActor::ActiveWidget_Implementation(bool Value)
{
	OnChangeActive.Broadcast(Value);
}

void AUnitActor::Hover(EHoverType HoverType)
{
	WidgetComponent->SetRelativeLocation(FVector::ForwardVector * SelectOffset);
	OnHovered.Broadcast(HoverType);
}

void AUnitActor::Unhover()
{
	WidgetComponent->SetRelativeLocation(FVector::Zero());
	OnUnhovered.Broadcast();
}

void AUnitActor::StartMovementAnimation()
{
	LastPos = GetActorLocation();
	if (MovementAnimCurve)
	{
		OnLocomotionChanged.Broadcast(true);
		Timeline.PlayFromStart();
	}
}

void AUnitActor::SetMovementAnimValue(float Value)
{
	const auto Result = FMath::Lerp(LastPos,CurrentSlot->GetActorLocation(),Value);
	SetActorLocation(Result);
}

void AUnitActor::EndMovementAnimation()
{
	OnLocomotionChanged.Broadcast(false);
	OnAnimFinished.Broadcast();
	OnAnimFinished.Clear();
}

void AUnitActor::AttachToSlot_Implementation(ABoardSlot* Slot)
{
	CurrentSlot = Slot;
}

bool AUnitActor::SelectionAllowed(int PlayerId)
{
	return Super::SelectionAllowed(PlayerId) && IsActivated() && !RedCard;
}

void AUnitActor::SetBattleState()
{
	InFormationState = false;
	ActiveVisibility();
}


void AUnitActor::SetCard_Implementation(UCardPreset* Card, UUniformPreset* Uniform, UColorPreset* Color,bool UseReserve)
{
	CardPreset = Card;
	UniformPreset = Uniform;
	ColorPreset = Color;
	UseReserveColor = UseReserve;
	DefaultPoints = Points = Card->Points;

#if WITH_EDITOR
	SetActorLabel(CardPreset->Name.ToString());
#endif
	
	OnSetup.Broadcast(this);

	const auto Widget = WidgetComponent->GetWidget();
	if(Widget->Implements<USetupSoccerActor>())
	{
		ISetupSoccerActor::Execute_Setup(Widget,this);
	}

	if(!IsLocal() && InFormationState)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}
