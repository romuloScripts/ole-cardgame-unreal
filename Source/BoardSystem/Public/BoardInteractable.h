// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BoardInteractable.generated.h"

UENUM(BlueprintType)
enum class EHoverType : uint8
{
	Select,
	FriendTarget,
	OpponentTarget,
	BlockedTarget,
	Highlight
};

class UMove;
UINTERFACE()
class BOARDSYSTEM_API UBoardInteractable : public UInterface
{
	GENERATED_BODY()
};

class BOARDSYSTEM_API IBoardInteractable
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Select(const bool Value);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Hover(EHoverType HoverType);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Unhover();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool InteractionAllowed(int PlayerId);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void PossibleTarget(bool value);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int GetOwnerPlayerId();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void TryMoveTo(AActor* Target);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UMove* GetMove(AActor* Target);
};
