// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserStatusStructs.h"
#include "GameFramework/SaveGame.h"
#include "OleSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DATA_API UOleSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)	
	FUserStatus UserStatus;
};
