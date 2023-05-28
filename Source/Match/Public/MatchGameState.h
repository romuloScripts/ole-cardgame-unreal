// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardPreset.h"
#include "GameFramework/GameState.h"
#include "GameStateEnums.h"
#include "UnitActor.h"
#include "MatchGameState.generated.h"

class UCard;
class AMatchPlayerController;
class AMatchPlayerState;
class ABoard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnStarted,int, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardPlayed,UCard*, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateMoveEnd,int, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGraveyardUpdate, TArray<UCard*>, GraveyardArray);

UCLASS()
class MATCH_API AMatchGameState : public AGameState
{
	GENERATED_BODY()
public:

	UPROPERTY(Replicated, BlueprintReadWrite)
	int CurrentTurnPlayer;

	UPROPERTY(Replicated, BlueprintReadWrite)
	float TurnTime;

	UPROPERTY(Replicated, BlueprintReadWrite)
	float TurnMaxTime;

	UPROPERTY(ReplicatedUsing=OnRep_TurnsUpdated, BlueprintReadWrite)
	int TotalTurns;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int MaxTurns;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int MaxCardsInHands;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int MaxLevelPoints = 2;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<AMatchPlayerState*> PlayersStateArray;

	UPROPERTY(ReplicatedUsing=OnRep_GraveyardUpdated, BlueprintReadWrite)
	TArray<UCard*> Graveyard;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnTurnChanged OnTurnChanged;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnTurnStarted OnTurnStarted;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnCardPlayed OnCardUsed;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnGraveyardUpdate OnGraveyardUpdate;

	UFUNCTION()
	void OnRep_TurnsUpdated();

	UFUNCTION()
	void OnRep_GraveyardUpdated() const;

	UFUNCTION(Server,Reliable)
	void SetWinner(int WinnerId);

	UFUNCTION(Server,Reliable)
	void SetSurrender(int SurrenderId);

	UFUNCTION(Server,Reliable)
	void SetDraw();

	AMatchPlayerState* GetPlayerStateById(int Id);

	EWinState GetWinState() const;

	int GetWinnerPlayerId() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetPlayerStates(TArray<AMatchPlayerState*> Array,const int MaxMana,const int StartMana);
	
	void AddTurnCount();

	void NextTurn();

	void StartTurn();

	void PlayersDrawCards(int Amount);
	
	void ResetUnitsInactiveStatus() const;

	UFUNCTION(BlueprintCallable)
	AMatchPlayerState* GetCurrentTurnPlayerState() const;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	AMatchPlayerState* GetOpponentPlayerState(AMatchPlayerState* PlayerState);

	virtual void BeginPlay() override;
	
	void SetMaxTurns(int Max);
	
	void SetBoard(ABoard* NewBoard);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool InMovement();

	UFUNCTION(BlueprintCallable)
	void AddCardToGraveyard(UCard* Card, bool UsedCard);

	UFUNCTION()
	ABoard* GetBoard();

protected:

	UPROPERTY(Replicated, BlueprintReadWrite)
	ABoard* Board;

	UPROPERTY(Replicated, BlueprintReadWrite)
	EWinState WinState = EWinState::None;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int WinnerPlayerId;

	UFUNCTION(NetMulticast,Reliable)
	void OnTurnStartEvent(int PlayerId);
};
