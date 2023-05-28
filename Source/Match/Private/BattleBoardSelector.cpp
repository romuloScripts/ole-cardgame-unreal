
#include "BattleBoardSelector.h"
#include "GameStateEnums.h"
#include "MatchPlayerController.h"
#include "MatchPlayerState.h"
#include "Move.h"

void UBattleBoardSelector::TickLocalPlayer()
{
	Super::TickLocalPlayer();
	if(HASONEFLAG(PlayerState->GetMoveState(),ETurnMoveState::WaitMove) == false)
	{
		if(State != EBoardSelectorState::Disable)
		{
			State = EBoardSelectorState::Disable;
			ClearSelections(true);
		}
		return;
	}

	if(State == EBoardSelectorState::Disable)
	{
		State = EBoardSelectorState::None;
	}
	UpdateSelectionState();
}


void UBattleBoardSelector::UpdateSelectionState()
{
	switch (State)
	{
	case EBoardSelectorState::None:
		NoneState();
		break;
	case EBoardSelectorState::Hover:
		HoverState();
		break;
	case EBoardSelectorState::Selected:
		SelectedState();
		break;
	case EBoardSelectorState::HoverTarget:
		HoverTargetState();
		break;
	default: NoneState(); break;
	}
}

void UBattleBoardSelector::NoneState()
{
	ClearSelections(true);
	if(!HoveredActor || !IBoardInteractable::Execute_InteractionAllowed(HoveredActor,PlayerController->GetId())) return;
	Super::NoneState();	
}

void UBattleBoardSelector::CheckDeselect()
{
	if(ClickedThisFrame)
	{
		NoneState();
	}
}

void UBattleBoardSelector::SelectedState()
{
	UpdateArrowPosition(SelectedActor->GetActorLocation());
	
	if(HoveredActor != SelectedActor)
	{
		if(LastHoveredActor && LastHoveredActor != SelectedActor)
		{
			IBoardInteractable::Execute_Unhover(LastHoveredActor);
			LastHoveredActor = nullptr;
		}
		
		if(HoveredActor == nullptr)
		{
			HideActionInfo();
			CheckDeselect();
			return;
		}

		if(const auto Move = IBoardInteractable::Execute_GetMove(SelectedActor,HoveredActor))
		{
			const bool Allowed = Move->Allowed(HoveredActor);
			LastHoveredActor = HoveredActor;
			State = EBoardSelectorState::HoverTarget;
			if(Allowed)
			{
				const bool Friend = PlayerController->GetId() == IBoardInteractable::Execute_GetOwnerPlayerId(LastHoveredActor);
				IBoardInteractable::Execute_Hover(LastHoveredActor,Friend ? EHoverType::FriendTarget : EHoverType::OpponentTarget);
			}else
			{
				IBoardInteractable::Execute_Hover(LastHoveredActor,EHoverType::BlockedTarget);
			}
			ShowActionInfo(Move,HoveredActor,Allowed);
			return;
		}
		HideActionInfo();
	}

	CheckDeselect();
}

void UBattleBoardSelector::TryExecuteMove()
{
	const auto Move = IBoardInteractable::Execute_GetMove(SelectedActor,HoveredActor);
	if(!Move) return;
	if(const bool Allowed = Move->Allowed(HoveredActor); !Allowed) return;
	const auto Selection = SelectedActor;
	const auto Target = ClickedActor;
	NoneState();
	ConfirmMove(Selection,Target);
}

void UBattleBoardSelector::HoverTargetState()
{
	UpdateArrowPosition(SelectedActor->GetActorLocation());
	
	if(HoveredActor != LastHoveredActor)
	{
		State = EBoardSelectorState::Selected;
	}else if(ClickedActor == LastHoveredActor)
	{
		TryExecuteMove();
	}else
	{
		CheckDeselect();
	}
}

void UBattleBoardSelector::ConfirmMove(AActor* Selection, AActor* Target) const
{
	PlayerController->ConfirmMove(Selection,Target);
}
