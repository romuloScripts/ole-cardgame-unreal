// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OleGameInstance.generated.h"


struct FPlayerStatus;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedMatchmakingTransition);

UCLASS()
class OLE_API UOleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSoftObjectPtr<UWorld> MenuMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSoftObjectPtr<UWorld> OnlineMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<class UMatchmakingWidget> MatchmakingWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TArray<FString> PlatformArray;

	UPROPERTY(BlueprintReadWrite, Category = Default)
	class UUserStatusController* UserStatusController;

	UPROPERTY(BlueprintReadWrite, Category = Default)
	UMatchmakingWidget* MatchmakingWidgetInstance;

	UPROPERTY()
	class USessionSubsystem* Session;

	UFUNCTION(BlueprintCallable,Exec)
    void Join();

	virtual void Init() override;

	virtual ULocalPlayer* CreateInitialPlayer(FString& OutError) override;

	UFUNCTION()
	void StartSession() const;

	UFUNCTION()
	void RemoveTeamScreen();

	UFUNCTION()
	void ShowMatchmakingOpponent(const FPlayerStatus& Player,const FPlayerStatus& Opponent) const;
	
	UFUNCTION()
	void CancelFindSessions();

	UFUNCTION(BlueprintCallable)
	void EndMatch();

	UPROPERTY()
	FOnFinishedMatchmakingTransition FinishedMatchmakingTransition;

protected:

	UFUNCTION()
	void Find(bool Successful);

	UFUNCTION()
	void OnCreateSessionComplete(bool Successful);

	void OnFindSessionsComplete(const TArray<FOnlineSessionSearchResult>& SessionResults, bool Successful);

	void OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result) const;

	UFUNCTION()
	void ShowMatchmakingWidget();
};


