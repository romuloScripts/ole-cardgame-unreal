// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BoardFunctionLibrary.generated.h"

class UStatComponent;
struct FPlayerStatus;
struct FBoardPlayerData;
class ABallActor;
class ABoardSlot;
enum class ECardType : uint8;
class UCardPreset;
class ASoccerActor;
class AMatchGameState;
class ABoard;
class AGoalkeeperActor;
class AMatchPlayerState;
class AUnitActor;
class AMatchPlayerController;
/**
 * 
 */
UCLASS()
class BOARDSYSTEM_API UBoardFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= Board)
	static bool HaveOpponentsInFront(bool Aerial,ABoardSlot* CurrentSlot, ASoccerActor* TargetActor,int TargetSlotGridX, int HorizontalDirection,int PlayerId);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool IsPassAllowed(ABoardSlot* TargetSlot,int MaxHorizontalDistance, bool& OpponentsInFront);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool IsKickAllowed(AGoalkeeperActor* GoalkeeperActor,int MaxHorizontalDistance,bool& OpponentsInFron);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool HaveUnitsInAllColumns(int PlayerId, ABoard* Board);

	UFUNCTION(BlueprintCallable, Category= Board)
	static int GetPlayerWithoutUnitsInAColumn(const TArray<FBoardPlayerData>& GameControllersArray, ABoard* Board);

	UFUNCTION(BlueprintCallable, Category= Board)
	static TArray<ABoardSlot*> GetMiddleColumnSlotsByPlayer(int PlayerId, ABoard* Board);

	UFUNCTION(BlueprintCallable, Category= Board)
	static TArray<ABoardSlot*> GetSlotsByPlayer(int PlayerId, ABoard* Board);

	UFUNCTION(BlueprintCallable, Category= Board)
	static TArray<ABoardSlot*> GetSlotsByColumn(ABoard* Board, const int Column);
	
	UFUNCTION(BlueprintCallable, Category= Board)
	static TArray<AUnitActor*> GetUnitsByType(TArray<AUnitActor*> UnitArray, const ECardType& CardType);

	UFUNCTION(BlueprintCallable, Category= Board)
	static AUnitActor* GetUnitByPresetAndPlayer(UCardPreset* Preset, APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category= Board)
	static int GetUnitNextLevelByPreset(UCardPreset* Preset, APlayerState* PlayerState);
	
	UFUNCTION(BlueprintCallable, Category= Board)
	static int GetUnitNextLevel(AUnitActor* Unit);

	UFUNCTION(BlueprintCallable,Category=Board,BlueprintPure)
	static ABoardSlot* GetSlotByActor(ASoccerActor* Actor);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool GetPlayersUseSameColor(const TArray<FPlayerStatus>& Players);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool BallInPossesOfOpponentGoalkeeper(ABoard* Board, int PlayerId);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool BallInPossesOfGoalkeeper(ABoard* Board, int PlayerId);

	UFUNCTION(BlueprintCallable, Category= Board)
	static bool BallInPossesOfActor(ASoccerActor* SoccerActor);

	UFUNCTION(BlueprintCallable, Category= Board,Meta=(DefaultToSelf="PlayerState"),BlueprintPure)
	static ABallActor* GetBall(const UObject* Object);

	UFUNCTION(BlueprintCallable,Category=Board,BlueprintPure)
	static TArray<AUnitActor*> GetAllUnits(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable,Category=Board,BlueprintPure)
	static TArray<AUnitActor*> GetAllUnitsOfPlayer(const FBoardPlayerData& PlayerData);

	UFUNCTION(BlueprintCallable,Category=Board,BlueprintPure)
	static bool AnySoccerActorCanExecuteMove(const FBoardPlayerData& PlayerState);

	UFUNCTION(BlueprintCallable,Category=Board,BlueprintPure,meta = (DeterminesOutputType = PlayerStateClass, DynamicOutputParam=OpponentPlayerState))
	static void GetOpponentPlayer(APlayerState* PlayerState, TSubclassOf<APlayerState> PlayerStateClass, APlayerState*& OpponentPlayerState);
	
	UFUNCTION(BlueprintCallable,Category=Board,Meta=(DefaultToSelf="Object"),BlueprintPure)
	static ABoard* GetBoardByObject(const UObject* Object);

	UFUNCTION(BlueprintCallable,Category=Board,Meta=(DefaultToSelf="Object"),BlueprintPure)
	static ABoard* GetBoard(const UObject* Object);

	UFUNCTION(BlueprintCallable,Category=Board,Meta=(DefaultToSelf="PlayerState"),BlueprintPure)
	static AGoalkeeperActor* GetGoalkeeperActor(const FBoardPlayerData& PlayerData, const bool Opponent);

	UFUNCTION(BlueprintCallable,Category=Board)
	static void MoveUnitsToDir(AUnitActor* Unit, bool UpDir);

	UFUNCTION(BlueprintCallable,Category=Board)
	static bool OpponentOnSide(AUnitActor* Unit, AUnitActor* Opponent, const bool HasToBeActive = true);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	static UStatComponent* GetStatComponent(const AActor* Actor);
};
