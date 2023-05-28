// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchPlayerState.h"
#include "MatchGameMode.h"
#include "Engine/ActorChannel.h"
#include "Kismet/GameplayStatics.h"
#include "DeckFunctionLibrary.h"
#include "AbilityContainer.h"
#include "Card.h"
#include "CardSelectTarget.h"
#include "RulesFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

AMatchPlayerState::AMatchPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMatchPlayerState, PlayerStatus);
	DOREPLIFETIME(AMatchPlayerState, DeckHolder);
	DOREPLIFETIME(AMatchPlayerState, Graveyard);
	DOREPLIFETIME(AMatchPlayerState, HandCards);
	DOREPLIFETIME(AMatchPlayerState, BoardPlayerId);
	DOREPLIFETIME(AMatchPlayerState, CurrentMana);
	DOREPLIFETIME(AMatchPlayerState, StartTurnMana);
	DOREPLIFETIME(AMatchPlayerState, MaxMana);
	DOREPLIFETIME(AMatchPlayerState, NumGoals);
	DOREPLIFETIME(AMatchPlayerState, MoveState);
	DOREPLIFETIME(AMatchPlayerState, CardTarget);
}

void AMatchPlayerState::CanReplicateArray(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags,
	bool& WroteSomething, const TArray<UCard*> Array)
{
	for (auto& Item : Array)
	{
		WroteSomething |= Channel->ReplicateSubobject(Item, *Bunch, *RepFlags);
	}
}

bool AMatchPlayerState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	//if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, DeckHolder);
	//if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, Graveyard);
	//if(WroteSomething) return true;
	CanReplicateArray(Channel, Bunch, RepFlags, WroteSomething, HandCards);
	//if(WroteSomething) return true;
	WroteSomething |= Channel->ReplicateSubobject(CardTarget, *Bunch, *RepFlags);
	return WroteSomething;
}

void AMatchPlayerState::AddGoal_Implementation()
{
	NumGoals++;
}

void AMatchPlayerState::ShuffleCards_Implementation()
{
	DeckHolder = URulesFunctionLibrary::ShuffleCards(this,PlayerStatus.Deck.Cards);
}

void AMatchPlayerState::InvokeOnCardUsed_Implementation(UCard* Card)
{
	OnCardUsed.Broadcast(Card);
}

void AMatchPlayerState::InvokeOnRemoveCardInDeck_Implementation(const TArray<UCard*>& Cards)
{
	OnRemoveCardInDeck.Broadcast(Cards);
}

void AMatchPlayerState::InvokeOnTrapCardActivated_Implementation(UCard* Card)
{
	OnTrapCardActivated.Broadcast(Card);
}

void AMatchPlayerState::OnRep_OnManaChanged(int Amount) const
{
	OnManaChanged.Broadcast(Amount);
}

void AMatchPlayerState::AddMana(int Value)
{
	SetMana(Execute_GetMana(this)+Value);
}

int AMatchPlayerState::GetGoals() const
{
	return NumGoals;
}

void AMatchPlayerState::SetMana(int NewMana)
{
	CurrentMana = FMath::Clamp(NewMana ,0,MaxMana);
	OnRep_OnManaChanged(CurrentMana);
}

void AMatchPlayerState::ConsumeMana_Implementation(int Amount)
{
	SetMana(Execute_GetMana(this)-Amount);
}

void AMatchPlayerState::AddStartTurnMana(int Value)
{
	StartTurnMana = FMath::Clamp(StartTurnMana+Value ,0,MaxMana);
}

int AMatchPlayerState::GetMana_Implementation() const
{
	return CurrentMana;
}

void AMatchPlayerState::ResetMana()
{
	SetMana(StartTurnMana);
}

void AMatchPlayerState::InitMana(int Max, int StartTurn)
{
	MaxMana = Max;
	StartTurnMana = StartTurn;
	SetMana(StartTurn);
}

int AMatchPlayerState::GetMaxMana() const
{
	return MaxMana;
}

int AMatchPlayerState::GetCardsAmountInDeckHolder() const
{
	return DeckHolder.Num();
}

void AMatchPlayerState::ReplaceCards(const TArray<int> CardsToReplace)
{
	const auto GameMode = Cast<AMatchGameMode>(UGameplayStatics::GetGameMode(this));

	if(GameMode == nullptr) return;
	TArray<UCard*> CardsToRemove;
	for(const auto Index : CardsToReplace)
	{
		auto Card = DeckHolder[Index];
		DeckHolder.Add(Card);
		CardsToRemove.Add(Card);
	}

	for(auto Card : CardsToRemove)
	{
		DeckHolder.RemoveSingle(Card);
	}
}

void AMatchPlayerState::CreateAbilityContainer()
{
	if(AbilityContainer == nullptr)
	{
		AbilityContainer = NewObject<UAbilityContainer>(this);
		AbilityContainer->Setup(this);
	}
}

void AMatchPlayerState::TryUseCard_Implementation(UCard* Card)
{
	if(!URulesFunctionLibrary::CanUseCard(Card,this)) return;
	if(Card->TargetRequired())
	{
		WaitCardTarget(Card);
	}else
	{
		UseCard(Card,Card->GetTargetContainers(this));
	}
}

void AMatchPlayerState::UseCard_Implementation(UCard* Card, const TArray<FCardDropTargetInfo>& DropInfo)
{
	if(!URulesFunctionLibrary::CanUseCard(Card,this)) return;
	Graveyard.Add(Card);
	HandCards.Remove(Card);
	Execute_ConsumeMana(this,URulesFunctionLibrary::GetManaCost(Card));
	InvokeOnCardUsed(Card);
	TArray<UCard*> Cards;
	Cards.Add(Card);
	InvokeOnRemovedCardInHand(Cards);
	URulesFunctionLibrary::DropCard(Card,DropInfo);
	MoveState = ETurnMoveState::WaitMoveBattle;
	CardTarget = nullptr;
	if(const auto GameState = URulesFunctionLibrary::GetOnlineGameState(GetWorld()))
	{
		GameState->AddCardToGraveyard(Card,true);
	} 
}

void AMatchPlayerState::WaitCardTarget_Implementation(UCard* Card)
{
	CardTarget = Cast<UCardSelectTarget>(Card->GetCardTarget(this));
	if(CardTarget == nullptr) return;
	MoveState = CardTarget->IsBoardTarget() ? ETurnMoveState::WaitSelectCardBoardTarget : ETurnMoveState::WaitSelectCardTarget;
	WaitCardTargetClientEvent(Card,CardTarget);
}

void AMatchPlayerState::CancelWaitCardTargetClientEvent_Implementation(UCard* Card)
{
	OnCancelWaitCardTargets.Broadcast(Card);
}

void AMatchPlayerState::WaitCardTargetClientEvent_Implementation(UCard* Card, UCardSelectTarget* Target)
{
	OnWaitCardTargets.Broadcast(Card,Target);
}

void AMatchPlayerState::InvokeOnRemovedCardInHand_Implementation(const TArray<UCard*>& Cards)
{
	OnRemovedCardInHand.Broadcast(Cards);
}

void AMatchPlayerState::InvokeOnCardsInDeckChanged_Implementation(const int Amount)
{
	OnCardsInDeckChanged.Broadcast(Amount);
}

void AMatchPlayerState::InvokeOnAddedCardInHand_Implementation(const TArray<UCard*>& Cards)
{
	OnAddCardInHand.Broadcast(Cards);
}

TArray<UCard*> AMatchPlayerState::GetCardsFromDeckHolderTop(int Amount) const
{
	TArray<UCard*> Cards;
	for (int i =0;i < Amount && i < DeckHolder.Num();i++)
	{
		Cards.Add(DeckHolder[i]);
	}
	return Cards;
}

void AMatchPlayerState::DrawCardsFromTop_Implementation(int Amount)
{
	DrawCards(GetCardsFromDeckHolderTop(Amount));
}

void AMatchPlayerState::DrawCards_Implementation(const TArray<UCard*>& Cards)
{
	const auto GameState = URulesFunctionLibrary::GetOnlineGameState(GetWorld());
	TArray<UCard*> CardsAdded;
	
	for (auto Card : Cards){
		if(!DeckHolder.Contains(Card) || HandCards.Num() >= GameState->MaxCardsInHands) continue;
		HandCards.Add(Card);
		CardsAdded.Add(Card);
		DeckHolder.Remove(Card);
	}
	if(CardsAdded.Num()<=0) return;
	InvokeOnAddedCardInHand(CardsAdded);
	InvokeOnCardsInDeckChanged(DeckHolder.Num());
}

void AMatchPlayerState::DiscardCards_Implementation(const TArray<UCard*>& Cards)
{
	for (auto Card : Cards)
	{
		DeckHolder.Remove(Card);
	}
	InvokeOnRemoveCardInDeck(Cards);
	InvokeOnCardsInDeckChanged(DeckHolder.Num());
}

void AMatchPlayerState::ReceiveCardTargetSelection_Implementation(UObject* Selection)
{
	if(!CardTarget || !HASONEFLAG(ETurnMoveState::WaitSelectCard,MoveState)) return;
	CardTarget->AddSelection(Selection);
	if(CardTarget->SelectionCompleted() && CardTarget->GetCard() != nullptr)
	{
		UseCard(CardTarget->GetCard(),CardTarget->GetTargets());
	}
}

void AMatchPlayerState::RemoveCardTargetSelection_Implementation(UObject* Selection)
{
	if(!CardTarget || !HASONEFLAG(ETurnMoveState::WaitSelectCard,MoveState)) return;
	CardTarget->RemoveSelection(Selection);
}

void AMatchPlayerState::CancelCardTarget_Implementation()
{
	if(!CardTarget || !HASONEFLAG(ETurnMoveState::WaitSelectCard,MoveState)) return;
	MoveState = ETurnMoveState::WaitMoveBattle;
	const auto OldCardTarget = CardTarget;
	CardTarget = nullptr;
	CancelWaitCardTargetClientEvent(OldCardTarget->GetCard());
}

void AMatchPlayerState::MoveBegin()
{
	MoveState = ETurnMoveState::Moving;
}

bool AMatchPlayerState::InMovement()
{
	return MoveState == ETurnMoveState::Moving;
}

void AMatchPlayerState::MoveEnded()
{
	if(MoveState != ETurnMoveState::Moving) return;
	MoveState = ETurnMoveState::None;
	OnMoveEnd.Broadcast(BoardPlayerId);
}

void AMatchPlayerState::SetMoveState(const ETurnMoveState TurnMoveState)
{
	MoveState = TurnMoveState;
	if(MoveState == ETurnMoveState::None)
	{
		CardTarget = nullptr;
	}
}

ETurnMoveState AMatchPlayerState::GetMoveState() const
{
	return MoveState;
}

UCardSelectTarget* AMatchPlayerState::GetCardTarget() const
{
	return CardTarget;
}

void AMatchPlayerState::BeginPlay()
{
	CreateAbilityContainer();
}

void AMatchPlayerState::SetUseReserveColor_Implementation()
{
	PlayerStatus.UseReserveColor = true;
}

bool AMatchPlayerState::GetUseReserveColor() const
{
	return PlayerStatus.UseReserveColor;
}

void AMatchPlayerState::RemoveAllCardsOfPreset_Implementation(UCardPreset* CardPreset)
{
	TArray<UCard*> RemovedCards;
	
	for (int i = HandCards.Num() -1; i >= 0; i--){
		const auto Card = HandCards[i];
		if(Card->GetPreset() != CardPreset) continue;
		RemovedCards.Add(Card);
		HandCards.Remove(Card);
	}

	for (int i = DeckHolder.Num() -1; i >= 0; i--){
		const auto Card = DeckHolder[i];
		if(Card->GetPreset() != CardPreset) continue;
		DeckHolder.Remove(Card);
	}
	
	InvokeOnRemovedCardInHand(RemovedCards);
	InvokeOnCardsInDeckChanged(DeckHolder.Num());
}

