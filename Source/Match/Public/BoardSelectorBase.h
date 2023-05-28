// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardInteractable.h"
#include "BoardSelectorBase.generated.h"

class UBoardSelectorWidgetBase;
class AArrowActor;
class UMove;
class AMatchPlayerController;
class AMatchPlayerState;

UENUM(BlueprintType)
enum class EBoardSelectorState : uint8
{
	Disable,
	None,
	Hover,
	Selected,
	HoverTarget,
};

UCLASS(Abstract,BlueprintType)
class MATCH_API UBoardSelectorBase : public UActorComponent
{
	GENERATED_BODY()

public:

	UBoardSelectorBase();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	EBoardSelectorState GetState() const;

	UFUNCTION()
	bool InSelectionState() const;
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EHoverType DefaultHoverType = EHoverType::Select;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBoardSelectorWidgetBase> ActionInfoClass;

	UPROPERTY(BlueprintReadWrite, Category = Cards)
	UBoardSelectorWidgetBase* ActionScreen;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<AArrowActor> ArrowClass;

	UPROPERTY(BlueprintReadWrite)
	AArrowActor* Arrow;

	UPROPERTY(BlueprintReadWrite)
	EBoardSelectorState State = EBoardSelectorState::Disable;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite)
	AMatchPlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite)
	AActor* SelectedActor;

	UPROPERTY(BlueprintReadWrite)
	AActor* LastHoveredActor;

	UPROPERTY(BlueprintReadWrite)
	AActor* PressedActor;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* ClickedActor;

	UPROPERTY(BlueprintReadWrite)
	AActor* HoveredActor;

	UPROPERTY(BlueprintReadWrite)
	bool ClickedThisFrame;

	virtual void BeginPlay() override;
	
	virtual void TickLocalPlayer();

	void UpdateMouseEvents();

	AActor* GetHoverActor() const;

	void ClearSelections(const bool HideArrow);

	void HideActionInfo() const;

	void ShowActionInfo(UMove* Move, const AActor* Hover, const bool Allowed) const;

	void UpdateArrowPosition(const FVector Origin) const;

	virtual void ActiveGrids() const;

	virtual void DisableGrids();

	virtual void NoneState();
	virtual void HoverState();
	virtual void SelectedState();
};
