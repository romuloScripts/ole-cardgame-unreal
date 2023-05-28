// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitActor.h"
#include "BoardSlot.generated.h"

class AGoalkeeperActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPossibleSelection, bool, Value);

UCLASS()
class BOARDSYSTEM_API ABoardSlot : public AActor, public IBoardInteractable
{
	GENERATED_BODY()

public:

	ABoardSlot();

	UPROPERTY(Replicated,BlueprintReadWrite)
	FIntPoint GridId;

	UPROPERTY(Replicated, BlueprintReadWrite)
	ECardType CardType;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int PlayerId;

	UPROPERTY(Replicated, BlueprintReadWrite)
	ABoardSlot* UpSlot;

	UPROPERTY(Replicated, BlueprintReadWrite)
	ABoardSlot* DownSlot;

	UPROPERTY(Replicated, BlueprintReadWrite)
	ABoardSlot* RightSlot;

	UPROPERTY(Replicated, BlueprintReadWrite)
	ABoardSlot* LeftSlot;

	UPROPERTY(Replicated, BlueprintReadWrite)
	AGoalkeeperActor* RightGoalkeeper;

	UPROPERTY(Replicated, BlueprintReadWrite)
	AGoalkeeperActor* LeftGoalkeeper;

	UPROPERTY(Replicated, BlueprintReadWrite)
	AUnitActor* AttachedUnit;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* GridWidgetComponent;

	UPROPERTY()
	FOnSlotHovered OnSlotHovered;

	UPROPERTY()
	FOnSlotHovered OnSlotUnhovered;

	UPROPERTY()
	FOnPossibleSelection OnPossibleSelection;

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void AttachUnit(AUnitActor* Unit);
	
	virtual void Select_Implementation(const bool Value) override;
	
	virtual void Hover_Implementation(EHoverType HoverType) override;
	
	virtual void Unhover_Implementation() override;

	virtual void PossibleTarget_Implementation(bool value) override;

	virtual int GetOwnerPlayerId_Implementation() override;
	
	virtual bool InteractionAllowed_Implementation(int Player) override;

	virtual void TryMoveTo_Implementation(AActor* Target) override;
	
	virtual UMove* GetMove_Implementation(AActor* Target) override;

protected:

	UPROPERTY()
	UUserWidget* HighlightWidget;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InvertLocation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
