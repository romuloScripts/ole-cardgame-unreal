// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MatchPlayerState.h"
#include "BoardSelectorBase.h"
#include "GameFramework/PlayerController.h"
#include "MatchPlayerController.generated.h"

class UMatchHUDBase;
enum class EWinState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCanSpendMana,int, Value);

UCLASS()
class MATCH_API AMatchPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UMatchHUDBase> MatchHudClass;
	
	FTimerHandle GetDeckTimer;

	UPROPERTY(BlueprintReadWrite)
	FOnCanSpendMana OnCanSpendMana;

	UPROPERTY(BlueprintReadWrite,Replicated)
	AMatchPlayerState* PlayerStateRef;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool MatchmakingTransitionEnded;
	
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool EndTurnRequested;
	
	AMatchPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void GetAndReturnDeck();
	
	UFUNCTION(Client, Reliable)
    void Login();

	UFUNCTION(Server, Reliable)
    void ReturnDeck(const FPlayerStatus& User);

	UFUNCTION(Client, Reliable)
    void ShowOpponentInMatchmaking(const FPlayerStatus& PlayerStatus,const FPlayerStatus& Opponent);

	UFUNCTION()
    void MatchmakingTransitionFinished();

	UFUNCTION(Server,Reliable)
	void ConfirmMove(AActor* Selection,AActor* Target);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void RequestEndTurn();

	UFUNCTION(Server, Reliable)
    void MatchmakingTransitionFinishedServer();

	UFUNCTION(Server, Reliable)
	void BattleStarted();

	UFUNCTION(Server, Reliable)
    void SetMulliganReplaceCards(const TArray<int>& CardsToReplace);

	UFUNCTION(Server, Reliable)
	void StartTurn();
	
	void DisableAllInteractions();

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	int GetId() const;

	UFUNCTION(BlueprintCallable)
	bool InteractionActive() const;

	UFUNCTION(BlueprintCallable)
	ETurnMoveState GetInteractionMode() const;

	UFUNCTION(BlueprintCallable,Client,Reliable)
	void CanSpendMana(int ManaValue);

	UFUNCTION(BlueprintCallable,Server, Reliable)
	void Surrender();

	UFUNCTION(BlueprintCallable)
	UMatchHUDBase* GetMatchHud() const;
	
	bool InSelectionState() const;

	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,meta = (AllowPrivateAccess = "true"))
	UBoardSelectorBase* BattleBoardSelector;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,meta = (AllowPrivateAccess = "true"))
	UBoardSelectorBase* CardTargetBoardSelector;

	UPROPERTY(Replicated)
	UMatchHUDBase* MatchHud;
};
