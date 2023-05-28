// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardSlot.h"

#include "Highlight.h"
#include "Net/UnrealNetwork.h"

void ABoardSlot::BeginPlay()
{
    Super::BeginPlay();
    HighlightWidget = GridWidgetComponent->GetWidget();
    if(HasAuthority()) return;
    InvertLocation();
}

void ABoardSlot::InvertLocation()
{
    auto Location = GetActorLocation();
    auto Local = GetActorRotation().RotateVector(Location);
    AddActorLocalOffset(FVector(0,Local.Y *-2,0));
}

void ABoardSlot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABoardSlot, GridId);
    DOREPLIFETIME(ABoardSlot, CardType);
    DOREPLIFETIME(ABoardSlot, PlayerId);
    DOREPLIFETIME(ABoardSlot, UpSlot);
    DOREPLIFETIME(ABoardSlot, DownSlot);
    DOREPLIFETIME(ABoardSlot, RightSlot);
    DOREPLIFETIME(ABoardSlot, LeftSlot);
    DOREPLIFETIME(ABoardSlot, RightGoalkeeper);
    DOREPLIFETIME(ABoardSlot, LeftGoalkeeper);
    DOREPLIFETIME(ABoardSlot, AttachedUnit);
}

void ABoardSlot::AttachUnit_Implementation(AUnitActor* Unit)
{
    AttachedUnit = Unit;
}

ABoardSlot::ABoardSlot()
{
    const auto SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);
    GridWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GridWidgetComponent"));
    GridWidgetComponent->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

void ABoardSlot::Select_Implementation(const bool bValue)
{
    if(!AttachedUnit) return;
    AttachedUnit->Selected(bValue);
}

void ABoardSlot::Hover_Implementation(EHoverType HoverType)
{
    OnSlotHovered.Broadcast();
    if(HighlightWidget)
    {
        IHighlight::Execute_Hover(HighlightWidget);
    }
    if(!AttachedUnit) return;
    AttachedUnit->Hover(HoverType);
}

void ABoardSlot::Unhover_Implementation()
{
    OnSlotUnhovered.Broadcast();
    if(HighlightWidget)
    {
        IHighlight::Execute_Unhover(HighlightWidget);
    }
    if(!AttachedUnit) return;
    AttachedUnit->Unhover();
}

void ABoardSlot::PossibleTarget_Implementation(bool value)
{
    OnPossibleSelection.Broadcast(value);
    if(HighlightWidget)
    {
        IHighlight::Execute_Active(HighlightWidget,value);
    }
}

int ABoardSlot::GetOwnerPlayerId_Implementation()
{
    return PlayerId;
}

bool ABoardSlot::InteractionAllowed_Implementation(int Player)
{
    return PlayerId == Player && AttachedUnit && AttachedUnit->SelectionAllowed(PlayerId);
}

void ABoardSlot::TryMoveTo_Implementation(AActor* Target)
{
    if(AttachedUnit) AttachedUnit->TryExecuteMove(Target);
}

UMove* ABoardSlot::GetMove_Implementation(AActor* Target)
{
    if(AttachedUnit == nullptr) return nullptr;
    return AttachedUnit->ActorValidMove(Target);
}
