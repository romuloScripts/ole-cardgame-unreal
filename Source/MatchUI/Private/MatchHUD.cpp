// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchHUD.h"
#include "Card.h"
#include "CardContainer.h"
#include "CardFunctionLibrary.h"
#include "CardPlayedWidget.h"
#include "CoinFlip.h"
#include "GoalScreenWidget.h"
#include "HudWidget.h"
#include "MatchGameState.h"
#include "MatchPlayerController.h"
#include "MulliganWidget.h"
#include "NotificationContainer.h"
#include "TeamFormationWidget.h"
#include "UserStatusStructs.h"
#include "VictoryWidget.h"
#include "Kismet/GameplayStatics.h"

FVector UMatchHUD::GetCardWidgetArrowOriginPos()
{
	return HudWidget->CardPlayedPlayer->GetCardWidgetArrowOriginPos();
}

void UMatchHUD::ShowFlipCoinScreen_Implementation(bool First)
{
	if(!CoinFlipWidget) return;
	CoinFlip = Cast<UCoinFlip>(CreateWidget(GetPlayerController(),CoinFlipWidget));
	CoinFlip->AddToViewport();
	CoinFlip->OnCoinFlipFinished.AddDynamic(this,&UMatchHUD::CoinFlipFinished);
	CoinFlip->PlayCoinFlip(First);
}

void UMatchHUD::CoinFlipFinished()
{
	CoinFlip->RemoveFromParent();
	CoinFlipFinishedServer();
}

void UMatchHUD::CoinFlipFinishedServer_Implementation()
{
	CoinFlipEnded = true;
}

void UMatchHUD::CreateHud_Implementation(AMatchPlayerState* Opponent)
{
	HudWidget = CreateWidget<UHudWidget>(GetPlayerController(),HudClass);
	HudWidget->AddToViewport();
	HudWidget->StartStates(PlayerController,PlayerController->PlayerStateRef, Opponent);
}

void UMatchHUD::ShowMulliganCards_Implementation(const TArray<UCardPreset*>& DeckHolderCards)
{
	if(!MulliganWidget) return;
	Mulligan = Cast<UMulliganWidget>(CreateWidget(GetPlayerController(),MulliganWidget));
	Mulligan->AddToViewport();
	Mulligan->SetUser(PlayerController,PlayerController->PlayerStateRef);
	TArray<FCardWithLevel> Cards;
	for(const auto Card : DeckHolderCards)
	{
		FCardWithLevel CardWithLevel;
		CardWithLevel.CardPreset = Card;
		CardWithLevel.Level = UCardFunctionLibrary::IsUnitCard(Card) ? 1 : 0;
		Cards.Add(CardWithLevel);
	}
	Mulligan->SetCards(Cards);
}

void UMatchHUD::GetMulliganReplaceCards_Implementation()
{
	TArray<int> Cards;
	if(Mulligan != nullptr)
	{
		Mulligan->GetReplaceCards(Cards);
		Mulligan->RemoveFromParent();
		Mulligan = nullptr;
	}
	PlayerController->SetMulliganReplaceCards(Cards);
}

void UMatchHUD::ShowVictory_Implementation(const EPlayerVictoryState& VictoryState)
{
	if(VictoryWidget == nullptr) return;
	const auto Victory = CreateWidget<UVictoryWidget>(GetPlayerController(),VictoryWidget);
	const auto GameState = Cast<AMatchGameState>(UGameplayStatics::GetGameState(GetWorld()));
	Victory->ShowScreen(VictoryState,PlayerController->PlayerStateRef,GameState->GetOpponentPlayerState(PlayerController->PlayerStateRef));
}

void UMatchHUD::RemoveTeamFormation_Implementation()
{
	if(TeamFormationWidget)
	{
		TeamFormationWidget->RemoveFromParent();
		TeamFormationWidget = nullptr;
	}
}

void UMatchHUD::ShowTeamFormation_Implementation()
{
	if(!TeamFormationWidgetClass)
	{
		PlayerController->RequestEndTurn();
		return;
	}
	TeamFormationWidget = Cast<UTeamFormationWidget>(CreateWidget(GetPlayerController(),TeamFormationWidgetClass));
	TeamFormationWidget->AddToViewport();
	TeamFormationWidget->SetUser(PlayerController,PlayerController->PlayerStateRef);
}

void UMatchHUD::GoalScreenFinished_Implementation()
{
	GoalScreenEnded = true;
}

void UMatchHUD::GoalScreen_Implementation(int PlayerId)
{
	AMatchGameState* GameState = Cast<AMatchGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if(!GoalWidgetClass || !GameState)
	{
		GoalScreenFinished();
		return;
	}
	const auto GoalWidget = Cast<UGoalScreenWidget>(CreateWidget(GetPlayerController(),GoalWidgetClass));
	GoalWidget->AddToViewport();
	GoalWidget->OnFinishedTransition.AddDynamic(this,&ThisClass::GoalScreenFinished);
	const auto Target = GameState->GetPlayerStateById(PlayerId);
	GoalWidget->UpdateColorAndReserve(Target->PlayerStatus.ColorPalette,Target->PlayerStatus.UseReserveColor);
	GoalWidget->PlayAnim(PlayerController->GetId() != PlayerId);
}

bool UMatchHUD::ShowCardPreview(UCardPreset* Card, const FPlayerStatus& PlayerStatus)
{
	if(CardPreview && !CardPreview->IsInViewport()) CardPreview = nullptr;
	if(CardPreview || !Card) return false;
	if(PlayerController->InSelectionState()) return false;
	CardPreview = CreateWidget<UCardContainer>(GetPlayerController(),CardPreviewClass);
	CardPreview->AddToViewport(10);
	CardPreview->UseReserveColor = PlayerStatus.UseReserveColor;
	CardPreview->UpdateAllPResets(Card,0,PlayerStatus.Uniform,PlayerStatus.ColorPalette,PlayerStatus.UseReserveColor);
	return true;
}

void UMatchHUD::ShowRedCardMessage_Implementation(UCardPreset* CardPreset, bool Opponent)
{
	if(!MessageClass) return;
	const auto Notification = Cast<UNotificationContainer>(CreateWidget(GetPlayerController(),MessageClass));
	Notification->AddToViewport();
	const auto Message = Opponent ? RedCardOpponentMessage : RedCardMessage;
	Notification->AnimSpeed = 0.25f;
	Notification->SetNotification(FText::Format(Message,FText::FromName(CardPreset->Name)));
}

void UMatchHUD::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AMatchPlayerController>(GetPlayerController());
}

APlayerController* UMatchHUD::GetPlayerController() const
{
	return Cast<APlayerController>(GetOwner());
}

