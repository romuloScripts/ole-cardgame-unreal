// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MatchHUDBase.generated.h"

enum class EPlayerVictoryState : uint8;
class AMatchPlayerState;
struct FPlayerStatus;
class UCardPreset;

UCLASS(Abstract)
class MATCH_API UMatchHUDBase : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool CoinFlipEnded;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool MulliganEnded;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool GoalScreenEnded;

	UMatchHUDBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	virtual bool ShowCardPreview(UCardPreset* Card, const FPlayerStatus& PlayerStatus);

	UFUNCTION(BlueprintCallable,Client,Reliable)
	virtual void ShowRedCardMessage(UCardPreset* CardPreset, bool Opponent);

	UFUNCTION()
	virtual FVector GetCardWidgetArrowOriginPos();

	UFUNCTION(Client, Reliable)
	virtual void ShowFlipCoinScreen(bool First);

	UFUNCTION()
	virtual void CoinFlipFinished();

	UFUNCTION(Server, Reliable)
	virtual void CoinFlipFinishedServer();

	UFUNCTION(Client, Reliable)
	virtual void ShowMulliganCards(const TArray<UCardPreset*>& DeckHolderCards);

	UFUNCTION(Client, Reliable,BlueprintCallable)
	virtual void GetMulliganReplaceCards();

	UFUNCTION(Client, Reliable)
	virtual void GoalScreen(int PlayerId);

	UFUNCTION(Server,Reliable)
	virtual void GoalScreenFinished();

	UFUNCTION(Client, Reliable)
	virtual void ShowTeamFormation();

	UFUNCTION(Client, Reliable)
	virtual void RemoveTeamFormation();
	
	UFUNCTION(Client, Reliable)
	virtual void ShowVictory(const EPlayerVictoryState& VictoryState);

	UFUNCTION(Client, Reliable)
	virtual void CreateHud(AMatchPlayerState* Opponent);
};
