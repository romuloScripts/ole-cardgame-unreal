// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardSelectorBase.h"
#include "ArrowActor.h"
#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "MatchPlayerController.h"
#include "Move.h"
#include "Kismet/KismetMathLibrary.h"
#include "BoardSelectorWidgetBase.h"

UBoardSelectorBase::UBoardSelectorBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBoardSelectorBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AMatchPlayerController>(GetOwner());
	if(PlayerController->IsLocalController())
	{
		PlayerState = PlayerController->PlayerStateRef;
		Arrow = GetWorld()->SpawnActor<AArrowActor>(ArrowClass);
		if(Arrow)
		{
			Arrow->Hide();
		}
		ActionScreen = CreateWidget<UBoardSelectorWidgetBase>(PlayerController,ActionInfoClass);
		ActionScreen->AddToViewport();
	}else
	{
		PrimaryComponentTick.SetTickFunctionEnable(false);
	}
}

void UBoardSelectorBase::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!PlayerController->IsLocalController()) return;
	if(!PlayerState) PlayerState = PlayerController->PlayerStateRef;
	if(!PlayerState) return;
	TickLocalPlayer();
}

EBoardSelectorState UBoardSelectorBase::GetState() const
{
	return State;
}

bool UBoardSelectorBase::InSelectionState() const
{
	return !Arrow->IsHidden();
}

void UBoardSelectorBase::TickLocalPlayer()
{
	UpdateMouseEvents();
}

void UBoardSelectorBase::UpdateMouseEvents()
{
	ClickedThisFrame = PlayerController->WasInputKeyJustReleased(EKeys::LeftMouseButton) || PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton);
	ClickedActor = nullptr;
	HoveredActor = GetHoverActor();
	if(PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton) ){
		PressedActor = HoveredActor;
	}else if(PressedActor && !PlayerController->IsInputKeyDown(EKeys::LeftMouseButton)){
		if(PressedActor == HoveredActor)
		{
			ClickedActor =  HoveredActor;
		}
		PressedActor = nullptr;
	}
}

AActor* UBoardSelectorBase::GetHoverActor() const
{
	FHitResult Hit;
	PlayerController->GetHitResultUnderCursor(ECC_WorldDynamic, false, Hit);
     
	if (Hit.bBlockingHit && Hit.GetActor() && Hit.GetActor()->Implements<UBoardInteractable>())
	{
		return Hit.GetActor();
	}
	return nullptr;
}

void UBoardSelectorBase::ClearSelections(const bool HideArrow)
{
	if(State != EBoardSelectorState::Disable) State = EBoardSelectorState::None;
	if(LastHoveredActor) IBoardInteractable::Execute_Unhover(LastHoveredActor);
	if(SelectedActor) IBoardInteractable::Execute_Select(SelectedActor,false);
	LastHoveredActor = nullptr;
	SelectedActor = nullptr;
	if(Arrow && HideArrow)
	{
		Arrow->Hide();
	}
	HideActionInfo();
	if(HideArrow) DisableGrids();
}

void UBoardSelectorBase::HideActionInfo() const
{
	if(ActionScreen)
	{
		if(!ActionScreen->IsHidden()) PlayerController->CanSpendMana(0);
		ActionScreen->HideActionInfo();
	}
}

void UBoardSelectorBase::ShowActionInfo(UMove* Move, const AActor* Hover, const bool Allowed) const
{
	if(Move == nullptr || ActionScreen == nullptr) return;
	PlayerController->CanSpendMana(Allowed && Move->CurrentManaCost > 0 ? Move->CurrentManaCost : 0);
	ActionScreen->ShowActionInfo(Hover->GetActorLocation(),Move->CurrentManaCost,Move->GetActionInfo(),!Allowed);
}

void UBoardSelectorBase::UpdateArrowPosition(const FVector Origin) const
{
	if(!Arrow) return;
	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation,WorldDirection);
	float T;
	FVector Intersection;
	FVector P1 = Origin;
	P1.X += 40;
	if(UKismetMathLibrary::LinePlaneIntersection_OriginNormal(WorldLocation, WorldLocation + (WorldDirection * 10000000),
		P1, FVector::ForwardVector,T,Intersection))
	{
		const FVector P2 = Intersection;
		Arrow->SetPos(P1,P2);
	}else
	{
		Arrow->Hide();
	}
}

void UBoardSelectorBase::ActiveGrids() const
{
	const auto Board = UBoardFunctionLibrary::GetBoard(this);
	for (auto Interactable : Board->GetAllInteractables())
	{
		const auto Target = Cast<AActor>(Interactable.GetObject());
		const auto Move = IBoardInteractable::Execute_GetMove(SelectedActor,Target);
		IBoardInteractable::Execute_PossibleTarget(Interactable.GetObject(),Move && Move->Allowed(Target));
	}
}

void UBoardSelectorBase::DisableGrids()
{
	const auto Board = UBoardFunctionLibrary::GetBoard(this);
	for (auto Interactable : Board->GetAllInteractables())
	{
		IBoardInteractable::Execute_PossibleTarget(Interactable.GetObject(),false);
	}
}

void UBoardSelectorBase::NoneState()
{
	if(!HoveredActor) return;
	LastHoveredActor = HoveredActor;
	IBoardInteractable::Execute_Hover(LastHoveredActor,DefaultHoverType);
	State = EBoardSelectorState::Hover;
}

void UBoardSelectorBase::HoverState()
{
	if(HoveredActor != LastHoveredActor)
	{
		State = EBoardSelectorState::None;
	}else if(ClickedActor == LastHoveredActor)
	{
		SelectedActor = ClickedActor;
		IBoardInteractable::Execute_Select(SelectedActor,true);
		ActiveGrids();
		State = EBoardSelectorState::Selected;
	}
}

void UBoardSelectorBase::SelectedState()
{
}
