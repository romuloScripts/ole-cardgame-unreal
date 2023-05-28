// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusContainer.h"

#include "MatchPlayerState.h"

void UPlayerStatusContainer::SetUser(AMatchPlayerState* State, AMatchPlayerController* Controller)
{
	PlayerState = State;
	SetStatus(PlayerState->PlayerStatus);
	PlayerController = Controller;
}

void UPlayerStatusContainer::SetStatus(FPlayerStatus NewPlayerStatus)
{
	PlayerStatus = NewPlayerStatus;
}
