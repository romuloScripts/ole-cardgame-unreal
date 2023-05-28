// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BoardSlot.h"
#include "BoardColumn.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBoardColumn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardType CardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerId;
};
