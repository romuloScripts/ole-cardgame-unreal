#include "../Public/OleGameInstance.h"

#include <limits>

#include "DeckFunctionLibrary.h"
#include "MatchmakingWidget.h"
#include "SessionSubsystem.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"

void UOleGameInstance::Init()
{
	Super::Init();
	Session = GetSubsystem<USessionSubsystem>();
}

void UOleGameInstance::Join()
{
	ShowMatchmakingWidget();
	Session->OnDestroySessionCompleteEvent.AddDynamic(this,&ThisClass::Find);
	Session->DestroySession();
}

ULocalPlayer* UOleGameInstance::CreateInitialPlayer(FString& OutError)
{
	const auto Player = Super::CreateInitialPlayer(OutError);
	UserStatusController = Player->GetSubsystem<UUserStatusController>();
	return Player;
}

void UOleGameInstance::Find(bool Successful)
{
	Session->OnDestroySessionCompleteEvent.RemoveDynamic(this,&ThisClass::Find);
	Session->OnFindSessionsCompleteEvent.AddUObject(this,&ThisClass::OnFindSessionsComplete);
	Session->FindSessions(10);
}

void UOleGameInstance::OnFindSessionsComplete(const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful)
{
	GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Green, FString::Printf( TEXT("FindSessionsComplete, Succeeded: %d"), Successful));
	Session->OnFindSessionsCompleteEvent.RemoveAll(this);
	
	if (Successful && SessionResults.Num() > 0)
	{
		Session->OnJoinGameSessionCompleteEvent.AddUObject(this,&ThisClass::OnJoinSessionComplete);
		Session->JoinGameSession(SessionResults[0]);
	}
	else 
	{
		Session->OnCreateSessionCompleteEvent.AddDynamic(this,&ThisClass::OnCreateSessionComplete);
		Session->CreateSession(2);
	}
}

void UOleGameInstance::EndMatch()
{
	if(GetEngine() && GetWorld())
	{
		GetEngine()->HandleDisconnect(GetWorld(), GetWorld()->GetNetDriver());
	}
}

void UOleGameInstance::ShowMatchmakingWidget()
{
	if(MatchmakingWidget == nullptr) return;
	MatchmakingWidgetInstance = CreateWidget<UMatchmakingWidget>(this, MatchmakingWidget);
	GetGameViewportClient()->AddViewportWidgetContent(MatchmakingWidgetInstance->TakeWidget(),std::numeric_limits<int32>::max());
	MatchmakingWidgetInstance->SetPlayer(UDeckFunctionLibrary::CreatePlayerStatus(UserStatusController));
	MatchmakingWidgetInstance->Cancel->OnClicked.AddDynamic(this,&ThisClass::CancelFindSessions);
}

void UOleGameInstance::ShowMatchmakingOpponent(const FPlayerStatus& Player,const FPlayerStatus& Opponent) const
{
	if(MatchmakingWidgetInstance == nullptr)
	{
		FinishedMatchmakingTransition.Broadcast();
		return;
	} 
	MatchmakingWidgetInstance->SetPlayer(Player);
	MatchmakingWidgetInstance->SetOpponent(Opponent);
	MatchmakingWidgetInstance->PlayMatchFoundAnimation();
	MatchmakingWidgetInstance->OnFinishedTransition.AddDynamic(this,&ThisClass::RemoveTeamScreen);
}

void UOleGameInstance::CancelFindSessions()
{
	RemoveTeamScreen();
	Session->CancelFindSessions();
	Session->OnFindSessionsCompleteEvent.RemoveAll(this);
	Session->DestroySession();
	const UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	UGameplayStatics::OpenLevelBySoftObjectPtr(World, MenuMap,true);
}

void UOleGameInstance::OnCreateSessionComplete(bool Successful)
{
	Session->OnCreateSessionCompleteEvent.RemoveDynamic(this,&ThisClass::OnCreateSessionComplete);
	if (Successful)
	{
		GEngine->AddOnScreenDebugMessage(100, 5, FColor::Green, TEXT("Hosting"));
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), OnlineMap, true, "listen");
	}
}

void UOleGameInstance::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result) const
{
	Session->OnJoinGameSessionCompleteEvent.RemoveAll(this);
	if(Result == EOnJoinSessionCompleteResult::Success)
	{
		Session->TravelToCurrentSession();
	}
}

void UOleGameInstance::StartSession() const
{
	Session->StartSession();
}

void UOleGameInstance::RemoveTeamScreen()
{
	if(MatchmakingWidgetInstance)
	{
		FinishedMatchmakingTransition.Broadcast();
		FinishedMatchmakingTransition.Clear();
		GetGameViewportClient()->RemoveViewportWidgetContent(MatchmakingWidgetInstance->TakeWidget());
		MatchmakingWidgetInstance = nullptr;
	}
}

// void UMainGameInstance::Init()
// {
// 	Super::Init();
//
// 	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMainGameInstance::BeginLoadingScreen);
// 	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMainGameInstance::EndLoadingScreen);
// }
//
// void UMainGameInstance::BeginLoadingScreen(const FString& InMapName)
// {
// 	FLoadingScreenAttributes LoadingScreen;
// 	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
//
// 	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
// 	LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();
//
// 	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
// }
//
// void UMainGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
// {
//
// }




