// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Phase.h"
#include "UObject/Object.h"
#include "BattlePhase.generated.h"

class AUnitActor;
class UCard;

UCLASS(Abstract)
class MATCH_API UBattlePhase : public UPhase
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool GoalHappened;

	UPROPERTY()
	bool WaitGoalScreenEnd;

	UPROPERTY()
	bool GoalkeeperHeldBall1Turn;
	
	void StartBoard() const;

	void NextTurn();
	
	bool EndTurn();

	bool EndTurnByMove() const;

	bool EndTurnByTime();
	
	bool BattleTimeEnd();

	UFUNCTION()
	void OnMoveEnd(int Player);

	UFUNCTION()
	void OnMoveBegin(int Player);

	UFUNCTION()
	void OnCardUsed(UCard* Card);

	UFUNCTION()
	void OnGoal(int PlayerId);

	UFUNCTION()
	void OnRedCard(AUnitActor* UnitActor);

	void SetVictory();

	void StartTurn();
	
	virtual void OnBegin(const FGameContext& Context) override;

	virtual bool EndIf() override;
	
	void TurnCountdown(float Delta);
	
	bool GoalEnded();
	
	void WaitGoalEnd();

	virtual void UpdatePhase(float Delta) override;
	
	void StartControllers();

	virtual void OnEnd() override;
	
};
