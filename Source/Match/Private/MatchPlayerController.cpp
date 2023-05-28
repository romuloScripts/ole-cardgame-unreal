#include "MatchPlayerController.h"
#include "Engine/World.h"
#include "OleGameInstance.h"
#include "MatchGameMode.h"
#include "MatchPlayerState.h"
#include "BattleBoardSelector.h"
#include "CardTargetBoardSelector.h"
#include "Engine/DemoNetDriver.h"
#include "DeckFunctionLibrary.h"
#include "MatchHUDBase.h"
#include "Kismet/GameplayStatics.h"

AMatchPlayerController::AMatchPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
	BattleBoardSelector = CreateDefaultSubobject<UBattleBoardSelector>(TEXT("BattleBoardSelector"));
	AddOwnedComponent(BattleBoardSelector);
	CardTargetBoardSelector = CreateDefaultSubobject<UCardTargetBoardSelector>(TEXT("CardTargetBoardSelector"));
	AddOwnedComponent(CardTargetBoardSelector);
}

void AMatchPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMatchPlayerController, MatchmakingTransitionEnded);
	DOREPLIFETIME(AMatchPlayerController, EndTurnRequested);
	DOREPLIFETIME(AMatchPlayerController, PlayerStateRef);
	DOREPLIFETIME(AMatchPlayerController, MatchHud);
}

void AMatchPlayerController::GetAndReturnDeck_Implementation()
{
	if(const auto GameInstance = Cast<UOleGameInstance>(GetGameInstance()))
	{
		PlayerStateRef = GetPlayerState<AMatchPlayerState>();
		PlayerStateRef->PlayerStatus = UDeckFunctionLibrary::CreatePlayerStatus(GameInstance->UserStatusController);
		ReturnDeck(PlayerStateRef->PlayerStatus);
	}
}

void AMatchPlayerController::Login_Implementation()
{
	GetWorldTimerManager().SetTimer(GetDeckTimer, this, &AMatchPlayerController::GetAndReturnDeck, 0.2f, false);
}

void AMatchPlayerController::ReturnDeck_Implementation(const FPlayerStatus& User)
{
	PlayerStateRef = GetPlayerState<AMatchPlayerState>();
	PlayerStateRef->PlayerStatus = User;
	if(AMatchGameMode* OnlineGameMode = Cast<AMatchGameMode>(GetWorld()->GetAuthGameMode()))
	{
		OnlineGameMode->FinishLogin(this);
	}
}

void AMatchPlayerController::ShowOpponentInMatchmaking_Implementation(const FPlayerStatus& PlayerStatus,const FPlayerStatus& Opponent)
{
	const auto GameInstance = Cast<UOleGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		GameInstance->FinishedMatchmakingTransition.AddDynamic(this,&AMatchPlayerController::MatchmakingTransitionFinished);
		GameInstance->ShowMatchmakingOpponent(PlayerStatus, Opponent);
	}else
	{
		MatchmakingTransitionFinished();
	}
}

void AMatchPlayerController::MatchmakingTransitionFinished()
{
	MatchmakingTransitionFinishedServer();
}

void AMatchPlayerController::MatchmakingTransitionFinishedServer_Implementation()
{
	MatchmakingTransitionEnded = true;
}

void AMatchPlayerController::BattleStarted_Implementation()
{
	const auto GameState = Cast<AMatchGameState>(UGameplayStatics::GetGameState(GetWorld()));
	MatchHud->CreateHud(GameState->GetOpponentPlayerState(PlayerStateRef));
}

void AMatchPlayerController::SetMulliganReplaceCards_Implementation(const TArray<int>& CardsToReplace)
{
	if(MatchHud->MulliganEnded) return;
	MatchHud->MulliganEnded = true;
	PlayerStateRef->ReplaceCards(CardsToReplace);
}

void AMatchPlayerController::StartTurn_Implementation()
{
	EndTurnRequested = false;
}

void AMatchPlayerController::DisableAllInteractions()
{
	EndTurnRequested = false;
	PlayerStateRef->SetMoveState(ETurnMoveState::None);
}

void AMatchPlayerController::RequestEndTurn_Implementation()
{
	EndTurnRequested = true;
}

void AMatchPlayerController::ConfirmMove_Implementation(AActor* Selection, AActor* Target)
{
	if(HASONEFLAG(PlayerStateRef->GetMoveState(),ETurnMoveState::WaitMove))
	{
		IBoardInteractable::Execute_TryMoveTo(Selection,Target);
	}
}

void AMatchPlayerController::TickActor(float DeltaTime, ELevelTick Tick, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, Tick, ThisTickFunction);
}

int AMatchPlayerController::GetId() const
{
	return PlayerStateRef->BoardPlayerId;
}

bool AMatchPlayerController::InteractionActive() const
{
	const auto Current = PlayerStateRef->GetMoveState();
	const bool Disabled = Current == ETurnMoveState::None || Current == ETurnMoveState::Moving || Current == ETurnMoveState::ShowCardSelected;
	return !Disabled;
}

ETurnMoveState AMatchPlayerController::GetInteractionMode() const
{
	return PlayerStateRef->GetMoveState();
}

UMatchHUDBase* AMatchPlayerController::GetMatchHud() const
{
	return MatchHud;
}

bool AMatchPlayerController::InSelectionState() const
{
	return BattleBoardSelector->InSelectionState() || CardTargetBoardSelector->InSelectionState();
}

void AMatchPlayerController::BeginPlay()
{
	if(HasAuthority())
	{
		MatchHud = Cast<UMatchHUDBase>(AddComponentByClass(MatchHudClass,false,FTransform(),false));
	}
	Super::BeginPlay();
}

void AMatchPlayerController::Surrender_Implementation()
{
	const auto GameMode = Cast<AMatchGameMode>(UGameplayStatics::GetGameMode(this));
	if(!GameMode) return;
	GameMode->Surrender(PlayerStateRef->BoardPlayerId);
}

void AMatchPlayerController::CanSpendMana_Implementation(int ManaValue)
{
	OnCanSpendMana.Broadcast(ManaValue);
}

