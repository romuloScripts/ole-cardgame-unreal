// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContainsMana.h"
#include "UserStatusStructs.h"
#include "GameFramework/PlayerState.h"
#include "MatchPlayerState.generated.h"

struct FCardDropTargetInfo;
class UCardSelectTarget;
class UAbilityContainer;
class UCard;
UENUM(BlueprintType)
enum class EPlayerVictoryState : uint8
{
	Lose, 
	Win,
	Draw
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardsInDeckChanged,int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged,int, Mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddCardInHand,const TArray<UCard*>&, Cards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveCardInDeck,const TArray<UCard*>&, Cards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardUsed,UCard*, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWaitCardTargets,UCard*, Card,UCardSelectTarget*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCancelWaitCardTargets,UCard*, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveEnd,int, PlayerId);


UCLASS()
class MATCH_API AMatchPlayerState : public APlayerState, public IContainsMana
{
	GENERATED_BODY()
public:

	AMatchPlayerState();

	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite)
	FPlayerStatus PlayerStatus;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<UCard*> DeckHolder;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<UCard*> Graveyard;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<UCard*> HandCards;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int BoardPlayerId;

	UPROPERTY(BlueprintReadWrite)
	UAbilityContainer* AbilityContainer;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnCardsInDeckChanged OnCardsInDeckChanged;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnAddCardInHand OnAddCardInHand;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnRemoveCardInDeck OnRemoveCardInDeck;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnAddCardInHand OnRemovedCardInHand;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnManaChanged OnManaChanged;
	
	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnCardUsed OnCardUsed;
	
	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnCardUsed OnTrapCardActivated;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnWaitCardTargets OnWaitCardTargets;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnCancelWaitCardTargets OnCancelWaitCardTargets;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnMoveEnd OnMoveEnd;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CanReplicateArray(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags, bool& WroteSomething, const TArray<UCard*> Array);

	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	UFUNCTION(BlueprintCallable)
	TArray<UCard*> GetCardsFromDeckHolderTop(int Amount) const;
	
	UFUNCTION(BlueprintCallable,Server,Reliable)
	void DrawCardsFromTop(int Amount);

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void DrawCards(const TArray<UCard*>& Cards);

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void DiscardCards(const TArray<UCard*>& Cards);

	UFUNCTION(Server,Reliable)
	void AddGoal();

	UFUNCTION(Server,Reliable)
	void ShuffleCards();

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnAddedCardInHand(const TArray<UCard*>& Cards);

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnRemoveCardInDeck(const TArray<UCard*>& Cards);

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnCardsInDeckChanged(int Amount);

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnRemovedCardInHand(const TArray<UCard*>& Cards);

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnCardUsed(UCard* Card);

	UFUNCTION(NetMulticast,Reliable)
	void InvokeOnTrapCardActivated(UCard* Card);

	UFUNCTION()
	void OnRep_OnManaChanged(int Amount) const;

	UFUNCTION(BlueprintCallable)
	void AddMana(int Value);

	UFUNCTION(BlueprintCallable)
	int GetGoals() const;

	UFUNCTION(BlueprintCallable)
	void SetMana(int NewMana);

	UFUNCTION(BlueprintCallable)
	virtual void ConsumeMana_Implementation(int Amount) override;

	UFUNCTION(BlueprintCallable)
	void AddStartTurnMana(int Value);

	UFUNCTION(BlueprintCallable)
	virtual int GetMana_Implementation() const override;

	UFUNCTION(BlueprintCallable)
	void ResetMana();

	void InitMana(int Max,int StartTurn);

	UFUNCTION(BlueprintCallable)
	int GetMaxMana() const;

	UFUNCTION(BlueprintCallable)
	int GetCardsAmountInDeckHolder() const;

	UFUNCTION(BlueprintCallable)
	void ReplaceCards(const TArray<int> CardsToReplace);

	UFUNCTION(BlueprintCallable)
	void CreateAbilityContainer();

	UFUNCTION(Server,Reliable)
	void WaitCardTarget(UCard* Card);

	UFUNCTION(Client,Reliable)
	void WaitCardTargetClientEvent(UCard* Card,UCardSelectTarget* Target);

	UFUNCTION(Client,Reliable)
	void CancelWaitCardTargetClientEvent(UCard* Card);

	UFUNCTION(Server,Reliable)
	void UseCard(UCard* Card,const TArray<FCardDropTargetInfo>& DropInfo);

	UFUNCTION(Server,Reliable)
	void TryUseCard(UCard* Card);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void ReceiveCardTargetSelection(UObject* Selection);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void RemoveCardTargetSelection(UObject* Selection);
	
	UFUNCTION(Server,Reliable,BlueprintCallable)
	void CancelCardTarget();

	UFUNCTION(BlueprintCallable)
	void MoveBegin();

	UFUNCTION(BlueprintCallable)
	bool InMovement();

	UFUNCTION(BlueprintCallable)
	void MoveEnded();

	UFUNCTION(BlueprintCallable)
	void SetMoveState(const ETurnMoveState TurnMoveState);

	UFUNCTION(BlueprintCallable)
	ETurnMoveState GetMoveState() const;

	UFUNCTION(BlueprintCallable)
	UCardSelectTarget* GetCardTarget() const;

	virtual void BeginPlay() override;

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void SetUseReserveColor();
	
	UFUNCTION(BlueprintCallable)
	bool GetUseReserveColor() const;

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void RemoveAllCardsOfPreset(UCardPreset* CardPreset);

protected:

	UPROPERTY(Replicated,BlueprintReadWrite)
	ETurnMoveState MoveState = ETurnMoveState::None;

	UPROPERTY(Replicated,BlueprintReadWrite)
	UCardSelectTarget* CardTarget;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int MaxMana;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int StartTurnMana;

	UPROPERTY(ReplicatedUsing=OnRep_OnManaChanged, BlueprintReadWrite)
	int CurrentMana;

	UPROPERTY(Replicated,BlueprintReadWrite)
	int NumGoals;
};
