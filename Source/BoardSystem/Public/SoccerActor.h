// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "WidgetComponentCustomCollision.h"
#include "GameFramework/Actor.h"
#include "ColorPreset.h"
#include "GameStateEnums.h"
#include "SoccerActor.generated.h"

class UCard;
class UCardPreset;
struct FBoardPlayerData;
class UStatComponent;
class UBallMove;
class UAbilityContainer;
class UMove;
class AMatchPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetup,ASoccerActor*, SoccerActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeActive,bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHovered,EHoverType, HoverType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnBeforeTakeDamage,ASoccerActor*, SoccerActor,int, Damage, bool, OpponentHasBall,AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnPostTakeDamage,ASoccerActor*, SoccerActor,EDamageType, DamageType,int, Damage,AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostForceDamage,int, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivePass,ASoccerActor*, OtherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivePoints,int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdatePoints,int, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAfterExecuteMove,UMove*, Move);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeTrapEffect, ETrapAbilityChange, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoveApplied, EMoveType, Move, EMoveDirection, Direction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMoveReceived, EMoveType, Move,EMoveDirection, Direction, bool, Success);

UCLASS(Abstract)
class BOARDSYSTEM_API ASoccerActor : public AActor
{
	GENERATED_BODY()
public:
	
	ASoccerActor();

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnMoveApplied OnMoveApplied;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnMoveReceived OnMoveReceived;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable, Category="Button|Event")
	FOnBeforeTakeDamage OnBeforeTakeDamage;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable, Category="Button|Event")
	FOnPostTakeDamage OnPostTakeDamage;

	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FOnReceivePass OnReceivePass;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnReceivePoints OnReceivePoints;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnAfterExecuteMove OnAfterExecuteMove;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnChangeTrapEffect OnChangeTrapEffect;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnPostForceDamage OnPostForceDamage;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnUpdatePoints OnUpdatePoints;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnSetup OnSetup;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnChangeActive OnChangeActive;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnHovered OnHovered;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnUnhovered OnUnhovered;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool UseReserveColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UColorPreset* ColorPreset;

	UPROPERTY(Replicated,EditAnywhere,BlueprintReadWrite,Category=Default)
	int DefaultPoints=1;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	UAbilityContainer* AbilityContainer;

	UFUNCTION(BlueprintCallable)
	APlayerState* GetOwnerPlayerState() const;

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void MoveApplied(EMoveType Move, AActor* Target);
	
	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void MoveReceived(EMoveType Move,AActor* Causer, bool Success);

	UFUNCTION(BlueprintCallable)
	virtual bool SelectionAllowed(int PlayerId);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void ReceivePointsEvent(int Value);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void PostForceDamage(int Damage);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	virtual void ResetPoints();

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void AddPoints(int Value, bool AddToDefault);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void AddDefaultPoints(int Value);
	
	UFUNCTION(BlueprintCallable)
	void SetPoints(int NewPoints);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Setup(UDataAsset* Preset, const FBoardPlayerData& State);

	UFUNCTION(Server, Reliable,BlueprintCallable)
	virtual void SetOwnerPlayer(int PlayerId, APlayerState* State);
	
	UFUNCTION(BlueprintCallable)
	void AttachBall(ABallActor* BallActor,ASoccerActor* OtherActor, bool bSetPos);

	UFUNCTION(BlueprintCallable)
	void DamageOther(ASoccerActor* Target,EDamageType DamageType,ABallActor* AttachedBall);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void PostTakeDamageEvent(EDamageType DamageType, int Damage, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	virtual void ReceiveDamage(int Damage, ABallActor* OtherAttachedBall,AActor* DamageCauser,EDamageType DamageType);

	UFUNCTION(BlueprintCallable)
	void ForceDamage(const int Damage);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void TryExecuteMove(AActor* Target); 
	
	UMove* ActorValidMove(AActor* Target);

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void TryExecuteBallMove(AActor* Target,ABallActor* Ball); 

	UFUNCTION()
	UMove* ActorValidBallMove(AActor* Target,ABallActor* Ball);

	UFUNCTION()
	bool CanExecuteAnyMove() const;

	UFUNCTION(BlueprintCallable)
	virtual void HoverActor() PURE_VIRTUAL(ASoccerActor::HoverActor, )
	
	UFUNCTION(BlueprintCallable)
	void UnhoverActor() PURE_VIRTUAL(ASoccerActor::UnhoverActor, );
	
	UFUNCTION(BlueprintCallable)
	void SelectActor(bool Value) PURE_VIRTUAL(ASoccerActor::SelectActor, );

	UFUNCTION(BlueprintCallable)
	bool IsActivated();

	UFUNCTION(BlueprintCallable)
	int GetPlayerId() const;

	UFUNCTION(BlueprintCallable)
	int GetPoints();

	UFUNCTION(BlueprintCallable)
	void SetBlockDamage(bool Block);

	UFUNCTION()
	USceneComponent* GetBallTargetPoint();

	UFUNCTION(BlueprintCallable)
	void AddBallMove(TSubclassOf<UBallMove> MoveClass);

	UFUNCTION(BlueprintCallable,meta = (DeterminesOutputType = MoveClass, DynamicOutputParam=SelectedMoves))
	void GetAllMovesOfType(TSubclassOf<UMove> MoveClass,TArray<UMove*>& SelectedMoves);


	UFUNCTION(BlueprintCallable)
	void MoveBegin();
	
	UFUNCTION(BlueprintCallable)
	void MoveEnd(UMove* Move) const;

	UFUNCTION(BlueprintCallable)
	UCardPreset* GetTrapCard();

	UFUNCTION(BlueprintCallable)
	bool IsLocal() const;

	UFUNCTION()
	APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool ContainsTrap() const;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetAttackedThisTurn();

protected:

	UPROPERTY(Replicated,BlueprintReadWrite)
	bool InFormationState=true;
	
	UPROPERTY(Replicated, BlueprintReadWrite)
	APlayerState* OwnerPlayerState;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int OwnerPlayerId;

	UPROPERTY(Replicated,BlueprintReadWrite)
	int Points;

	UPROPERTY(BlueprintReadWrite)
	bool BlockDamage;

	UPROPERTY(BlueprintReadWrite)
	bool Trap;

	UPROPERTY(BlueprintReadWrite,Replicated)
	bool AttackedThisTurn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite  = Default)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite  = Default)
	USceneComponent* BallTargetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite  = Default)
	UStatComponent* StatComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite  = Default)
	UWidgetComponentCustomCollision* WidgetComponent;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	TArray<UMove*> Moves;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	TArray<UMove*> BallMoves;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	TArray<UMove*> FormationMoves;

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	virtual void ActiveWidget(bool Value);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	virtual void ContainsTrapAbilityChanged(ETrapAbilityChange AbilityChange, UCard* Card);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	virtual void WidgetUpdatePoints(int NewPoints);

	virtual void BeginPlay() override;

	virtual void InitDefaultMoves() PURE_VIRTUAL(ASoccerActor::InitDefaultMoves, );

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CanReplicateArray(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags, bool& WroteSomething, const TArray<UMove*> Array);

	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
};
