#pragma once
#include "GameStateEnums.generated.h"

#define HASONEFLAG(Enum1,Enum2) ((static_cast<uint8>(Enum1) & static_cast<uint8>(Enum2)) >=1)

UENUM(BlueprintType)
enum class SelectedMode : uint8
{
	None,
	PVP,
};

UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	Up, 
	Down,
	Left,
	Right
};

UENUM(BlueprintType)
enum class EMoveType : uint8
{
	Pass, 
	Kick,
	Dribble,
	Dribbled,
};

UENUM(BlueprintType)
enum class EWinState : uint8
{
	None, 
	Win,
	Draw,
	Surrender,
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Dribble, 
	Foul,
	StealBall,
	Kick
};

UENUM(BlueprintType)
enum class ETrapAbilityChange : uint8
{
	Add, 
	Remove,
	Activated,
};

UENUM(meta = (Bitflags))
enum class ETurnMoveState : uint8
{
	None = (1 << 0),
	WaitMoveFormation = (1 << 1),
	WaitMoveBattle = (1 << 2),
	Moving = (1 << 3),
	ShowCardSelected = (1 << 4),
	WaitSelectCardBoardTarget = (1 << 5),
	WaitSelectCardTarget = (1 << 6),
	WaitMove = WaitMoveFormation | WaitMoveBattle,
	WaitSelectCard = WaitSelectCardBoardTarget | WaitSelectCardTarget,
	WaitUseCard = WaitMove | WaitSelectCard,
};

UENUM(BlueprintType)
enum class EEndGameResult : uint8
{
	Victory,
	Defeat,
	Draw,
};

UENUM(BlueprintType)
enum class ECardClass : uint8
{
	None  UMETA(DisplayName = "None"),
	Terra UMETA(DisplayName = "Terra"),
	Natu  UMETA(DisplayName = "Natu"),
	Zap   UMETA(DisplayName = "Zap"),
	Kai   UMETA(DisplayName = "Kai"),
};

UENUM(BlueprintType)
enum class ECardType : uint8
{
	None	  	    UMETA(DisplayName = "None"),
	Attacker		UMETA(DisplayName = "Attacker"),
	Midfield		UMETA(DisplayName = "Midfield"),
	Defender		UMETA(DisplayName = "Defender"),
	Effect			UMETA(DisplayName = "Effect"),
	Trap			UMETA(DisplayName = "Trap"),
};

UENUM(BlueprintType)
enum class ERarityType : uint8
{
	None		UMETA(DisplayName = "None"),
	Common		UMETA(DisplayName = "Common"),
	Rare		UMETA(DisplayName = "Rare"),
	Epic		UMETA(DisplayName = "Epic"),
	Legendary	UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class EPlayConditions : uint8
{
	WhenCardsInGraveyard UMETA(DisplayName = "Play when there are cards in the graveyard"),
};

UENUM(BlueprintType)
enum class ECardPurpose : uint8
{
	MakeGoals UMETA(DisplayName = "Make Goals"),
};


UENUM(BlueprintType)
enum class EPlayerSize : uint8
{
	Small UMETA(DisplayName = "Small (P)"),
	Medium UMETA(DisplayName = "Medium (M)"),
	Big UMETA(DisplayName = "Big (G)")
};
