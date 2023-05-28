#pragma once

#include "CoreMinimal.h"
#include "SoccerActor.h"
#include "Components/TimelineComponent.h"
#include "UnitActor.generated.h"

class UCardPreset;
struct FBoardPlayerData;
class UUnitGameplayWidget;
class UUnitMove;
class UUniformPreset;
class ABoardSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitLevelUp, int, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeYellowCard, bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangePoints, int, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocomotionChanged, bool, IsMoving);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRedCard, AUnitActor*, UnitActor);

UCLASS()
class BOARDSYSTEM_API AUnitActor : public ASoccerActor
{
	GENERATED_BODY()

public:
	AUnitActor();

	UFUNCTION()
	void InitAbilities();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AttachToSlot(ABoardSlot* Slot);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AttachToSlotAndTeleport(ABoardSlot* Slot);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void ToSlot(ABoardSlot* Slot);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void MoveToSlot(ABoardSlot* Slot);
	
	virtual void ActiveWidget_Implementation(bool Value) override;
	
	virtual void WidgetUpdatePoints_Implementation(int NewPoints) override;

	UFUNCTION()
	void LevelUp();

	UFUNCTION()
	void OnRep_OnLevelChanged() const;

	UFUNCTION()
	void OnRep_OnYellowCardChanged() const;

	UFUNCTION(NetMulticast, Reliable)
	void ActiveVisibility();

	UFUNCTION(BlueprintCallable)
	void Selected(bool Value);

	UFUNCTION(BlueprintCallable)
	void Hover(EHoverType HoverType);

	UFUNCTION(BlueprintCallable)
	void Unhover();
	
	UFUNCTION(BlueprintCallable)
	void StartMovementAnimation();

	UFUNCTION()
	void SetMovementAnimValue(float Value);

	UFUNCTION()
	void EndMovementAnimation();
	
	virtual bool SelectionAllowed(int PlayerId) override;
	
	UFUNCTION()
	void SetBattleState();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SetCard(UCardPreset* Card, UUniformPreset* Uniform,UColorPreset* Color,bool UseReserve);

	virtual void Setup(UDataAsset* Preset,const FBoardPlayerData& PlayerData) override;

	virtual void SetOwnerPlayer(int PlayerId, APlayerState* State) override;

	UFUNCTION()
	void AddYellowCard();

	UFUNCTION()
	bool GetYellowCard() const;

	UFUNCTION()
	void SetRedCard();

	UFUNCTION()
	bool GetRedCard() const;

	UFUNCTION()
	bool IsInMaxLevel() const;

protected:

	UPROPERTY(ReplicatedUsing=OnRep_OnYellowCardChanged,BlueprintReadWrite)
	bool YellowCard;

	UPROPERTY(Replicated,BlueprintReadWrite)
	bool RedCard;

	virtual void InitDefaultMoves() override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void InvertBallLocation() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<TSubclassOf<UUnitMove>> FormationMovesClasses;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<TSubclassOf<UUnitMove>> MovesClasses;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<TSubclassOf<UBallMove>> BallMovesClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* MovementAnimCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float SelectOffset= 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCardPreset* CardPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUniformPreset* UniformPreset;

	UPROPERTY(ReplicatedUsing=OnRep_OnLevelChanged,EditAnywhere, BlueprintReadWrite, Category = Default)
	int Level;

	UPROPERTY(Replicated,BlueprintReadWrite)
	ABoardSlot* CurrentSlot;

	UPROPERTY(BlueprintReadWrite)
	FVector LastPos;

	UPROPERTY()
	FTimeline Timeline;
	
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnAnimFinished OnAnimFinished;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnChangeYellowCard OnChangeYellowCard;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnUnitLevelUp OnLevelUp;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnChangePoints OnPointsChanged;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnLocomotionChanged OnLocomotionChanged;

	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnRedCard OnRedCardReceived;
};
