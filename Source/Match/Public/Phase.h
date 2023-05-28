// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchGameMode.h"
#include "UObject/Object.h"
#include "Phase.generated.h"

USTRUCT(BlueprintType)
struct FGameContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AMatchGameMode* GameMode;
	UPROPERTY(BlueprintReadWrite)
	AMatchGameState* GameState;
	UPROPERTY(BlueprintReadWrite)
	TArray<AMatchPlayerController*> GameControllersArray;
	UPROPERTY(BlueprintReadWrite)
	TArray<AMatchPlayerState*> PlayerStates;

	FGameContext(AMatchGameMode* GM,AMatchGameState* GS,TArray<AMatchPlayerController*> GControllers) : GameMode(GM) , GameState(GS), GameControllersArray(GControllers)
	{
		for(const auto PlayerController : GameControllersArray)
		{
			if(PlayerController->PlayerStateRef) PlayerStates.Add(PlayerController->PlayerStateRef);
		}
	}

	FGameContext(): GameMode(nullptr), GameState(nullptr)
	{
	}

	AMatchPlayerController* GetCurrentTurnPlayerController()
	{
		return  GameControllersArray[GameState->CurrentTurnPlayer];
	}

	AMatchPlayerState* GetCurrentTurnPlayerState() const
	{
		return  GameState->GetCurrentTurnPlayerState();
	}
};


UCLASS(Blueprintable,Abstract)
class MATCH_API UPhase : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	virtual void OnBegin(const FGameContext& Context);

	UFUNCTION(BlueprintCallable)
	virtual void OnEnd();

	UFUNCTION(BlueprintCallable)
	virtual void UpdatePhase(float Delta);

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UPhase> GetNextPhase();

	UFUNCTION(BlueprintCallable)
	virtual bool EndIf();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UPhase> NextPhase;
	
	UPROPERTY(BlueprintReadWrite)
	FGameContext GameContext;
};
