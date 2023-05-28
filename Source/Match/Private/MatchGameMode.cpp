

#include "MatchGameMode.h"
#include "OleGameInstance.h"
#include "CoreMinimal.h"
#include "Phase.h"
#include "MatchGameState.h"
#include "MatchPlayerController.h"

AMatchGameMode::AMatchGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStateRef = GetGameState<AMatchGameState>();
}

void AMatchGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (!HasAuthority()) return;
	const auto Player = Cast<AMatchPlayerController>(NewPlayer);
	if (!Player || GameControllersArray.Num() >= MaxNumPlayers) return;
	GameControllersArray.Add(Player);
	if(Player)
	{
		Player->Login();
	}
}

void AMatchGameMode::FinishLogin_Implementation(AController* Controller)
{
	if(GameControllersArray.Contains(Controller))
	{
		LoginCompleted++;
		if(BeginIf())
		{
			BeginMatch();
		}
	}
}

bool AMatchGameMode::BeginIf() const
{
	return GameControllersArray.Num() >= MaxNumPlayers && LoginCompleted == MaxNumPlayers;
}

void AMatchGameMode::BeginMatch()
{
	const auto GameInstance = Cast<UOleGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;

	GameInstance->StartSession();
	GameStateRef->SetMaxTurns(MaxTurns);
	TArray<AMatchPlayerState*> PlayerStates;
	for (const auto PlayerController : GameControllersArray)
	{
		PlayerStates.Add(PlayerController->PlayerStateRef);
	}
	GameStateRef->SetPlayerStates(PlayerStates,Mana_Max,Mana_Start);
	SetPhase(FirstPhase);
}

void AMatchGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	const auto Player = Cast<AMatchPlayerController>(Exiting);
	GameControllersArray.Remove(Player);
	if(GameControllersArray.Num() < MaxNumPlayers && CurrentPhase != nullptr) ReturnMainMenu();
}

void AMatchGameMode::ReturnMainMenu() const
{
	const auto GameInstance = Cast<UOleGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;
	GameInstance->EndMatch();
}

void AMatchGameMode::SetPhase(TSubclassOf<UPhase> NewPhase)
{
	EndPhase();
	if(NewPhase == nullptr)
	{
		CurrentPhase = nullptr;
	}else
	{
		CurrentPhase = NewObject<UPhase>(this,NewPhase);
		if(CurrentPhase)
		{
			CurrentPhase->OnBegin(FGameContext(this,GameStateRef,GameControllersArray));
		}
	}
}

void AMatchGameMode::UpdatePhase(float DeltaTime)
{
	if(!CurrentPhase) return;
	CurrentPhase->UpdatePhase(DeltaTime);
	if(CurrentPhase->EndIf())
	{
		const auto Next = CurrentPhase->GetNextPhase();
		SetPhase(Next);
	}
}

void AMatchGameMode::Surrender_Implementation(int PlayerId)
{
	GameStateRef->SetSurrender(PlayerId);
	if(GameStateRef->GetWinState() != EWinState::Surrender) return;
	SetPhase(SurrenderPhase);
}

void AMatchGameMode::TickActor(float DeltaTime, ELevelTick Tick, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, Tick, ThisTickFunction);
	UpdatePhase(DeltaTime);
}

void AMatchGameMode::EndPhase()
{
	if(!CurrentPhase) return;
	CurrentPhase->OnEnd();
	CurrentPhase = nullptr;
}

