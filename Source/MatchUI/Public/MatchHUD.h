// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchHUDBase.h"
#include "MatchHUD.generated.h"

class AMatchPlayerController;
class UCoinFlip;
class UGoalScreenWidget;
class UMulliganWidget;
class UTeamFormationWidget;
class UVictoryWidget;
class UCardContainer;
class UHudWidget;
/**
 * 
 */
UCLASS()
class MATCHUI_API UMatchHUD : public UMatchHUDBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UHudWidget> HudClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UCardContainer> CardPreviewClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=HUD)
	TSubclassOf<class UNotificationContainer> MessageClass;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=HUD)
	FText RedCardMessage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=HUD)
	FText RedCardOpponentMessage;

	UPROPERTY(BlueprintReadWrite, Category = Cards)
	UHudWidget* HudWidget;

	UPROPERTY(BlueprintReadWrite, Category = Cards)
	UCardContainer* CardPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UCoinFlip> CoinFlipWidget;

	UPROPERTY(BlueprintReadWrite)
	UCoinFlip* CoinFlip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UMulliganWidget> MulliganWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UTeamFormationWidget> TeamFormationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UGoalScreenWidget> GoalWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UMulliganWidget* Mulligan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TSubclassOf<UVictoryWidget> VictoryWidget;

	UPROPERTY()
	AMatchPlayerController* PlayerController;

	virtual FVector GetCardWidgetArrowOriginPos() override;
	virtual void ShowFlipCoinScreen_Implementation(bool First) override;
	virtual void CoinFlipFinished() override;
	virtual void CoinFlipFinishedServer_Implementation() override;
	virtual void CreateHud_Implementation(AMatchPlayerState* Opponent) override;
	virtual void ShowMulliganCards_Implementation(const TArray<UCardPreset*>& DeckHolderCards) override;
	virtual void GetMulliganReplaceCards_Implementation() override;
	virtual void ShowVictory_Implementation(const EPlayerVictoryState& VictoryState) override;
	virtual void RemoveTeamFormation_Implementation() override;
	virtual void ShowTeamFormation_Implementation() override;
	virtual void GoalScreenFinished_Implementation() override;
	virtual void GoalScreen_Implementation(int PlayerId) override;
	virtual bool ShowCardPreview(UCardPreset* Card, const FPlayerStatus& PlayerStatus) override;
	virtual void ShowRedCardMessage_Implementation(UCardPreset* CardPreset, bool Opponent) override;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite)
	UTeamFormationWidget* TeamFormationWidget;

	APlayerController* GetPlayerController() const;
};
