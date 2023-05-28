// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Phase.h"
#include "UObject/Object.h"
#include "TeamFormationPhase.generated.h"

/**
 * 
 */
UCLASS()
class MATCH_API UTeamFormationPhase : public UPhase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float TeamFormationMaxTime = 30;

	virtual void OnBegin(const FGameContext& Context) override;
	bool PlayersConfirmed() const;
	bool TurnEnded() const;

	virtual bool EndIf() override;

	virtual void OnEnd() override;

	virtual void UpdatePhase(float Delta) override;

protected:

	UFUNCTION(BlueprintCallable)
	void OnMoveBegin(int Player);

	UFUNCTION(BlueprintCallable)
	void OnMoveEnd(int Player);

	UPROPERTY(BlueprintReadWrite)
	TArray<AMatchPlayerController*> PlayersRemainingConfirmation;
};
