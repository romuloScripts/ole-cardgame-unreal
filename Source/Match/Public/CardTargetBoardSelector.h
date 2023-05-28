// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardSelectorBase.h"
#include "CardTargetBoardSelector.generated.h"

class ASoccerActor;
class UCardSelectTarget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MATCH_API UCardTargetBoardSelector : public UBoardSelectorBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	FVector CardPosition;

	UPROPERTY(BlueprintReadWrite)
	UCardSelectTarget* CardSelectTarget;
	
	virtual void TickLocalPlayer() override;
	void UpdateSelectionState();
	ASoccerActor* GetSoccerActor(AActor* Target) const;
	virtual void NoneState() override;
	virtual void HoverState() override;
	virtual void SelectedState() override;

	virtual void ActiveGrids() const override;

	virtual void DisableGrids() override;
};
