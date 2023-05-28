// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallActor.h"
#include "BoardSlot.h"
#include "GoalkeeperActor.generated.h"

class UGoalkeepersPreset;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickGoalkeeper, AGoalkeeperActor*, Goalkeeper);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlipVisual, bool, Flip);

UCLASS()
class BOARDSYSTEM_API AGoalkeeperActor : public ASoccerActor, public IBoardInteractable
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TArray<TSubclassOf<UBallMove>> BallMovesClasses;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<ABoardSlot*> NeighborSlots;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsHovered;

	UPROPERTY(BlueprintReadWrite)
	bool ReceivedGoal;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* GridWidgetComponent;

	UPROPERTY()
	FOnSlotHovered OnSlotHovered;

	UPROPERTY()
	FOnSlotHovered OnSlotUnhovered;

	UPROPERTY()
	FOnFlipVisual OnFlipVisual;

	UPROPERTY()
	FOnPossibleSelection OnPossibleSelection;

	AGoalkeeperActor();

	virtual void InitDefaultMoves() override;

	ABoardSlot* GetCloserSlot(FIntPoint Point);

	UFUNCTION(Server, Reliable,BlueprintCallable)
	void SetNeighbors(const TArray<ABoardSlot*>& Slots);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void SetData(UGoalkeepersPreset* GoalkeeperPreset,UColorPreset* Color,bool UseReserve);

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void SetLocation(FVector Location, FRotator Rotator,bool Right);

	virtual void Setup(UDataAsset* Preset, const FBoardPlayerData& PlayerData) override;
	
	virtual void ReceiveDamage(int OpponentPoints, ABallActor* OtherAttachedBall,AActor* DamageCauser,EDamageType DamageType) override;

	virtual void ResetPoints() override;
	
	virtual void Select_Implementation(const bool Value) override;
	
	virtual void Hover_Implementation(EHoverType HoverType) override;

	virtual int GetOwnerPlayerId_Implementation() override;
	
	virtual void Unhover_Implementation() override;
	
	virtual bool InteractionAllowed_Implementation(int Player) override;

	virtual void PossibleTarget_Implementation(bool value) override;

	virtual void TryMoveTo_Implementation(AActor* Target) override;
	
	virtual UMove* GetMove_Implementation(AActor* Target) override;

	UGoalkeepersPreset* GetPreset() const;
	UColorPreset* GetColor() const;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	UGoalkeepersPreset* GoalkepperPreset;

	UPROPERTY()
	UUserWidget* Highlight;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InvertLocation(bool Right);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
