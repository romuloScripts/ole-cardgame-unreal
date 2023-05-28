// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BallActor.h"
#include "BoardColumn.h"
#include "BoardSlot.h"
#include "GoalkeeperActor.h"
#include "UnitActor.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

struct FBoardPlayerData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoardGoal,int, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoardMoveEnd,int, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoardMoveBegin,int, PlayerId);

UCLASS(Blueprintable,BlueprintType,Abstract)
class BOARDSYSTEM_API ABoard : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category  =  "Settings")
	TSubclassOf<ABoardSlot> SlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<ABallActor> BallClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AUnitActor> UnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<AGoalkeeperActor> GoalkeeperClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category  = "Settings")
	FIntPoint GoalkeeperSlotVerticalRange = FIntPoint(1,2);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Settings")
	FVector2D TilesSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Settings")
	float Offset = 20;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Settings")
	int Lines = 4;

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category  = "Settings") 
	TArray<FBoardColumn> Columns;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	USceneComponent* GoalkeeperTarget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	USceneComponent* GoalkeeperTarget2;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UWidgetComponent* LockerRoom;

	UPROPERTY(Replicated,BlueprintReadWrite)
	ABallActor* BallActor;

	UPROPERTY(Replicated,BlueprintReadWrite)
	TArray<ABoardSlot*> SlotMap;

	UPROPERTY(Replicated,BlueprintReadWrite)
	TArray<AGoalkeeperActor*> Goalkeepers;

	ABoard();

	UFUNCTION(Server,Reliable)
	void StartPlayers(const TArray<FBoardPlayerData>& Players);

	UFUNCTION(Server,Reliable)
	void SpawnSoccerPlayers(const TArray<FBoardPlayerData>& Players);

	UFUNCTION()
	ABoardSlot* GetSlotAtPoint(FIntPoint Point);

	UFUNCTION()
	int GetSlotArrayIndex(const ABoardSlot* Slot) const;

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void StartBall(const int PlayerId);

	UFUNCTION(BlueprintCallable)
	void ResetUnitsInactiveStatus();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnAddCardToLockerRoom(APlayerState* Player);

	UFUNCTION(BlueprintCallable)
	TArray<AUnitActor*> GetAllUnits();

	TArray<TScriptInterface<IBoardInteractable>> GetAllInteractables();

	UFUNCTION(BlueprintCallable)
	void RemoveUnit(AUnitActor* UnitActorToRemove);

	UPROPERTY()
	FOnBoardGoal OnGoal;

	UFUNCTION(Server,Reliable)
	void Goal(const int PlayerId);

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnBoardMoveEnd OnMoveEnd;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnBoardMoveBegin OnMoveBegin;

	UFUNCTION(Server,Reliable)
	void MoveEnd(const int PlayerId);

	UFUNCTION(Server,Reliable)
	void MoveBegin(const int PlayerId);

protected:
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	TArray<AUnitActor*> AllUnitsArray;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void CreateSlots();

	UFUNCTION(BlueprintCallable)
	void SpawnGoalkeeper(const FBoardPlayerData& PlayerData);

	UFUNCTION(BlueprintCallable)
	void AddGoalkeeperToBoard(AGoalkeeperActor* Goalkeeper, USceneComponent* Target,bool Left);

	UFUNCTION(BlueprintCallable)
	void SpawnUnits(const FBoardPlayerData& PlayerData);

	UFUNCTION(BlueprintCallable)
	AUnitActor* SpawnUnit(const FBoardPlayerData& PlayerData, UCardPreset* Preset);

	UFUNCTION(BlueprintCallable)
	void AddSlot(FIntPoint Point, FBoardColumn Column);

	UFUNCTION(BlueprintCallable)
	void ConnectSlots();

	UFUNCTION(BlueprintCallable)
	ABoardSlot* AddConnection(FIntPoint Point);

	UFUNCTION(BlueprintCallable)
	void AddUnitsByColumn(const TArray<AUnitActor*>& UnitsPlayer,const int PlayerId);

	UFUNCTION(BlueprintCallable)
	void AddUnitToSlot(AUnitActor* Unit,ABoardSlot* Slot);
};
