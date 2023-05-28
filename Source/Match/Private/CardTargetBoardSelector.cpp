
#include "CardTargetBoardSelector.h"
#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "BoardSlot.h"
#include "MatchPlayerController.h"
#include "MatchPlayerState.h"
#include "CardSelectTarget.h"
#include "MatchHUDBase.h"

void UCardTargetBoardSelector::TickLocalPlayer()
{
	Super::TickLocalPlayer();
	if(PlayerState->GetMoveState() != ETurnMoveState::WaitSelectCardBoardTarget)
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

void UCardTargetBoardSelector::UpdateSelectionState()
{
	UpdateArrowPosition(CardPosition);
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
	default: NoneState(); break;
	}
}

ASoccerActor* UCardTargetBoardSelector::GetSoccerActor(AActor* Target) const
{
	auto BoardSlot = Cast<ABoardSlot>(Target);
	return Cast<ASoccerActor>(BoardSlot && BoardSlot->AttachedUnit ? BoardSlot->AttachedUnit : HoveredActor);
}

void UCardTargetBoardSelector::NoneState()
{
	UpdateArrowPosition(PlayerController->GetMatchHud()->GetCardWidgetArrowOriginPos());
	ClearSelections(false);
	if(!HoveredActor) return;
	UCardSelectTarget* CardTarget = PlayerState ? PlayerState->GetCardTarget() : nullptr;
	if(CardTarget && !CardSelectTarget)
	{
		CardSelectTarget = CardTarget;
		ActiveGrids();
	}
	if(CardTarget && CardTarget->AllowSelection(GetSoccerActor(HoveredActor)))
	{
		Super::NoneState();	
	}
}

void UCardTargetBoardSelector::HoverState()
{
	UpdateArrowPosition(PlayerController->GetMatchHud()->GetCardWidgetArrowOriginPos());
	Super::HoverState();
}

void UCardTargetBoardSelector::SelectedState()
{
	Super::SelectedState();
	PlayerState->ReceiveCardTargetSelection(GetSoccerActor(SelectedActor));
	ClearSelections(true);
}

void UCardTargetBoardSelector::ActiveGrids() const
{
	if(!CardSelectTarget) return;
	const auto Board = UBoardFunctionLibrary::GetBoard(this);
	for (auto Interactable : Board->GetAllInteractables())
	{
		const auto Target = Cast<AActor>(Interactable.GetObject());
		const auto Allow = CardSelectTarget->AllowSelection(GetSoccerActor(Target));
		IBoardInteractable::Execute_PossibleTarget(Interactable.GetObject(),Allow);
	}
}

void UCardTargetBoardSelector::DisableGrids()
{
	CardSelectTarget = nullptr;
	Super::DisableGrids();
}

