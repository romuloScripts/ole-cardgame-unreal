// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGameStructs.h"
#include "CardPreset.h"
#include "GoalkeeperPreset.h"
#include "DeckStructs.generated.h"


#define TEST_NONE(Bitmask) (Bitmask == 0)
#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)
#define SET_BIT(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint32>(Bit))
#define CLEAR_BIT(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint32>(Bit)))

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EDeckValidType : uint8
{
	None = 0 UMETA(Hidden),
    NoTotalCards = 1 << 0,
    NoAllUnits = 1 << 1,
};

ENUM_CLASS_FLAGS(EDeckValidType);

UENUM(BlueprintType)
enum class EAddCardDeniedType : uint8
{
	None,
    MaxCards,
    MaxUnitCards,
    MaxAttackers,
    MaxMidfilders,
    MaxDefenders,
    NoCardsInInventory,
};

USTRUCT(BlueprintType)
struct FDeckCardsAmount
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalCards=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UnitCards=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EffectCards=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TrapCards=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UniqueUnitCards=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UniqueAttackers=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UniqueMidfielders=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UniqueDefenders=0;
};

USTRUCT(BlueprintType)
struct FCardInDeck
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardPreset* Card;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;
};

USTRUCT(BlueprintType)
struct FDeck
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DeckName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CustomizationName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardClass CardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGoalkeepersPreset* GoalkeeperPreset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCardInDeck> Cards;
};

