// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserStatusStructs.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RulesFunctionLibrary.generated.h"

class UAbilityContainer;
class ASoccerActor;
class UCard;
struct FCardDropTargetInfo;
class UCardPreset;
class AMatchPlayerState;
class AMatchGameMode;
class AMatchGameState;
class AMatchPlayerController;
/**
 * 
 */
UCLASS()
class MATCH_API URulesFunctionLibrary :  public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= Rules)
	static int GetWinnerId(TArray<AMatchPlayerState*> GameControllersArray, AMatchGameState* GameState, AMatchGameMode* GameMode);

	UFUNCTION(BlueprintCallable, Category= Rules)
	static bool TurnEndedByMoves(AMatchGameState* GameState);

	UFUNCTION(BlueprintCallable, Category= Rules)
	static TArray<FBoardPlayerData> GetBoardPlayersData(const TArray<AMatchPlayerState*>& PlayerStates);

	UFUNCTION(BlueprintCallable, Category= Rules,BlueprintPure)
	static FBoardPlayerData GetBoardPlayerData(AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category= Rules)
	static int GetBetterScore(AMatchGameState* GameState);

	UFUNCTION(BlueprintCallable, Category= Rules)
	static bool IsPlayerTurn(const AMatchPlayerState* PlayerState);
	
	UFUNCTION(BlueprintCallable,Category= Deck)
	static TArray<UCard*> ShuffleCards(AMatchPlayerState* Owner, TArray<FCardInDeck> Deck);

	UFUNCTION(BlueprintCallable, Category = Card)
	static bool CanTryUseCard(UCard* Card, const AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category = Card)
	static bool CanUseCard(UCard* Card, const AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category = Card)
	static bool CanUseAnyCard(const AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category = Card)
	static bool CanUseAnyCardInHand(const AMatchPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static bool IsTrapAndTargetAlreadyHaveTrapCard(UCard* Card);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static bool IsTrapAndAbilityContainerHaveTrapCard(UCard* Card, const UAbilityContainer* AbilityContainer);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static bool IsTrapAndSoccerActorHaveTrapCard(UCard* Card, const ASoccerActor* SoccerActor);

	UFUNCTION(BlueprintCallable, Category = Card)
	static bool EnoughMana(UCard* Card,const AMatchPlayerState* PlayerState);
	
	UFUNCTION(BlueprintCallable, Category = Card)
	static UCard* FindCardInHand(TArray<UCard*> Cards, UCard* CardToFind);

	UFUNCTION(BlueprintCallable, Category = Card)
	static int GetManaCost(UCard* Card);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static TArray<UCardAbilityPreset*> GetAbility(const UCard* Card);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static TArray<FGameplayTag> GetPresetStats(UCardPreset* Preset);

	UFUNCTION(BlueprintCallable, Category = Card,BlueprintPure)
	static int GetNextLevel(UCard* Card);

	UFUNCTION(BlueprintCallable, Category = Card)
	static void DropCard(UCard* Card, const TArray<FCardDropTargetInfo>& DropInfos);

	UFUNCTION(BlueprintCallable,Category=Widget,Meta=(DefaultToSelf="Instigator"),BlueprintPure)
	static AMatchPlayerController* GetOnlinePlayerController(UObject* Instigator);

	UFUNCTION(BlueprintCallable, Category= Board,Meta=(DefaultToSelf="Object"))
	static AMatchGameState* GetOnlineGameState(const UObject* Object);

	UFUNCTION(BlueprintCallable, Category= Board,BlueprintPure)
	static AMatchGameState* GetOnlineGameStateByObject(UObject* Object);
};
