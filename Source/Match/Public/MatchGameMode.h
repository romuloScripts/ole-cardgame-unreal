// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchGameState.h"
#include "MatchPlayerController.h"
#include "GameFramework/GameMode.h"
#include "MatchGameMode.generated.h"

class UPhase;

UCLASS()
class MATCH_API AMatchGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UPhase> FirstPhase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UPhase> SurrenderPhase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int MaxGoals = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int Mana_Start = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int Mana_Max = 7;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int MaxNumPlayers = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int NumPlayersCardBegin = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int MaxCardsInHands = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int MaxTurns = 18;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxTurnTimeSeconds = 65;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AMatchPlayerController*> GameControllersArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMatchGameState* GameStateRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPhase* CurrentPhase;

	AMatchGameMode();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(Server, Reliable)
	virtual void FinishLogin(AController* Controller);

	bool BeginIf() const;

	UFUNCTION()
	void ReturnMainMenu() const;

	UFUNCTION(BlueprintCallable,Server, Reliable)
	void Surrender(int PlayerId);

protected:

	FTimerHandle Timer;

	int LoginCompleted;
	
	UFUNCTION()
	void BeginMatch();

	UFUNCTION(BlueprintCallable)
	void EndPhase();
	
	UFUNCTION(BlueprintCallable)
	void SetPhase(TSubclassOf<UPhase> NewPhase);
	
	void UpdatePhase(float DeltaTime);
	
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
};
