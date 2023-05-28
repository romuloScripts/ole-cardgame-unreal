// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoardSelectorBase.h"
#include "BattleBoardSelector.generated.h"

class UMove;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MATCH_API UBattleBoardSelector : public UBoardSelectorBase
{
	GENERATED_BODY()
	
protected:
	
	virtual void TickLocalPlayer() override;
	
	void CheckDeselect();

	void TryExecuteMove();
	void HoverTargetState();
	void UpdateSelectionState();
	void ConfirmMove(AActor* Selection, AActor* Target) const;
	virtual void NoneState() override;
	virtual void SelectedState() override;
};
