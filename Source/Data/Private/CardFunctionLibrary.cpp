// Fill out your copyright notice in the Description page of Project Settings.


#include "CardFunctionLibrary.h"
#include "CardPreset.h"
#include "GameStateEnums.h"

bool UCardFunctionLibrary::IsUnitCard(UCardPreset* Card)
{
	return Card->CardType == ECardType::Attacker || Card->CardType == ECardType::Defender || Card->CardType == ECardType::Midfield;
}

int UCardFunctionLibrary::GetPointsByLevel(UCardPreset* Preset, const int Level) 
{
	if(Preset->CardLevels.Num() <= 0) return Preset->Points;
	if(Level > Preset->CardLevels.Num())
	{
		return 2;
	}

	if(Level>0)
	{
		return Preset->CardLevels[Level-1].Points;
	}
	return Preset->Points;
}
