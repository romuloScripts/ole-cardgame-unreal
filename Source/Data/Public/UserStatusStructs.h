// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorPreset.h"
#include "CardPreset.h"
#include "DeckStructs.h"
#include "UniformPreset.h"
#include "CardBackPreset.h"
#include "EmblemPreset.h"
#include "UserStatusStructs.generated.h"

USTRUCT(BlueprintType)
struct FCustomizationData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CustomizationName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEmblemPreset* Emblem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUniformPreset* Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardBackPreset* CardBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UColorPreset* ColorPalette;
};

USTRUCT(BlueprintType)
struct FUserStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentDeck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentCustomization;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName,FDeck> Decks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName,FCustomizationData> Customizations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UCardPreset*,int> Cards;
};

USTRUCT(BlueprintType)
struct  FPlayerStatus
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UserName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEmblemPreset* Emblem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUniformPreset* Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardBackPreset* CardBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UColorPreset* ColorPalette;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDeck Deck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseReserveColor = false;
};

USTRUCT(BlueprintType)
struct  FBoardPlayerData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerStatus PlayerStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BoardIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AController* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerState* PlayerState;
};

USTRUCT(BlueprintType)
struct  FMatchStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerStatus Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerStatus Opponent;
};

