
#include "HandWidget.h"

#include "BoardFunctionLibrary.h"
#include "CardDragDropOperation.h"
#include "MatchPlayerController.h"
#include "NotificationContainer.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UnitActor.h"
#include "Card.h"
#include "CardInHandWidget.h"
#include "DropAreaWidget.h"
#include "RulesFunctionLibrary.h"

void UHandWidget::SetupCard(UCardInHandWidgetBase* CardVisual, UCard* Card)
{
	Super::SetupCard(CardVisual,Card);
	const auto PlayerCard = Cast<UCardInHandWidget>(CardVisual);
	PlayerCard->SetupCard(Card,PlayerStatus.Uniform,PlayerStatus.ColorPalette,PlayerStatus.UseReserveColor);
	if(!IsDesignTime())
	{
		if(PlayerState) ActiveCardInteraction(PlayerCard);
		PlayerCard->FOnTryInteract.AddDynamic(this,&UHandWidget::OnTryInteractWithCard);
	}
}

TSubclassOf<UCardInHandWidgetBase> UHandWidget::GetCardClass()
{
	return CardInHandClass;
}

void UHandWidget::UnhoverUnit()
{
	if(!SelectedUnit) return;
	SelectedUnit->Unhover();
	SelectedUnit = nullptr;
}

void UHandWidget::HoverUnit(const UCardDragDropOperation* const CardOperation)
{
	if(SelectedUnit || !CardOperation->Card || !CardOperation->Card->IsUnit()) return;
	SelectedUnit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(CardOperation->Card->GetPreset(),PlayerState);
	SelectedUnit->Hover(EHoverType::Highlight);
}

void UHandWidget::UpdateDragState()
{
	if(!PlayerController) return;
	const auto CardOperation = Cast<UCardDragDropOperation>(UWidgetBlueprintLibrary::GetDragDroppingContent());
	const bool DragCard = CardOperation != nullptr && PlayerController->GetInteractionMode() == ETurnMoveState::WaitMoveBattle;
	if(DragCard && !DraggingCard)
	{
		HoverUnit(CardOperation);
		PlayerController->CanSpendMana(URulesFunctionLibrary::GetManaCost(CardOperation->Card));
		DraggingCard = true;
		GetWorld()->GetTimerManager().ClearTimer(DisableDropAreaTimerHandle);
	}else if(!DragCard && DraggingCard && !GetWorld()->GetTimerManager().TimerExists(DisableDropAreaTimerHandle))
	{
		PlayerController->CanSpendMana(0);
		GetWorld()->GetTimerManager().SetTimer(DisableDropAreaTimerHandle,this,&UHandWidget::DisableDropArea,0.1f,false);
	}

	const bool ActiveDropArea = PlayerController->GetInteractionMode() == ETurnMoveState::WaitMoveBattle && DraggingCard;
	const auto Visible = ActiveDropArea ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	if(DropArea->GetVisibility() != Visible) DropArea->SetVisibility(Visible);
	if(DropArea->GetVisibility() != ESlateVisibility::Visible)
	{
		UnhoverUnit();
	}
}

void UHandWidget::UpdateActiveCards()
{
	for (const auto Card : Cards)
	{
		ActiveCardInteraction(Cast<UCardInHandWidget>(Card.Value));
	}
}

void UHandWidget::DisableDropArea()
{
	DraggingCard = false;
	UnhoverUnit();
}

void UHandWidget::OnTryInteractWithCard(UCardInHandWidget* CardInHandWidget)
{
	FText Message;
	if(URulesFunctionLibrary::IsTrapAndTargetAlreadyHaveTrapCard(CardInHandWidget->GetCardData()))
	{
		Message = AlreadyHaveTrapCardMessage;
	}
	else if(!URulesFunctionLibrary::EnoughMana(CardInHandWidget->GetCardData(),PlayerController->PlayerStateRef))
	{
		Message = NotEnoughManaMessage;
	}
	if(Message.IsEmpty() || !MessageClass) return;
	const auto Notification = Cast<UNotificationContainer>(CreateWidget(this,MessageClass));
	Notification->AddToViewport();
	Notification->SetNotification(Message);
}

void UHandWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateDragState(); 
	UpdateActiveCards();
}

void UHandWidget::SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller)
{
	Super::SetUser(State, Controller);
	PlayerState->OnManaChanged.AddDynamic(this,&UHandWidget::ManaChanged);
	if(DropArea) DropArea->SetReferences(this,PlayerState);
}

void UHandWidget::SetStatus(FPlayerStatus NewPlayerStatus)
{
	Super::SetStatus(NewPlayerStatus);
	for(const auto CardItem : Cards)
	{
		SetupCard(CardItem.Value,CardItem.Key);
	}
}

void UHandWidget::UseCard(UCard* Card)
{
	PlayerState->TryUseCard(Card);
}

void UHandWidget::ActiveCardInteraction(UCardInHandWidget* const Card)
{
	Card->ActiveInteraction(URulesFunctionLibrary::CanTryUseCard(Card->GetCardData(),PlayerController->PlayerStateRef));
}

void UHandWidget::ManaChanged(int Amount)
{
	for (const auto Card : Cards)
	{
		ActiveCardInteraction(Cast<UCardInHandWidget>(Card.Value));
	}
}
