// Fill out your copyright notice in the Description page of Project Settings.

#include "CardSystemFunctionLibrary.h"
#include "CardAbility.h"
#include "CardDropTargetInfo.h"
#include "CardPreset.h"

TArray<UCardAbilityPreset*> UCardSystemFunctionLibrary::GetAbilityByLevel(UCardPreset* Preset, int Level)
{
	Level = FMath::Clamp(Level,0,Preset->CardLevels.Num());
	return Level > 0 ? Preset->CardLevels[Level-1].AbilityPresets : Preset->AbilityPresets;
}

UCardAbility* UCardSystemFunctionLibrary::CreateAbility(const FCardDropTargetInfo& DropInfo, UCardAbilityPreset* CardAbilityPreset, UCard* Card)
{
	const auto CardAbility = NewObject<UCardAbility>(DropInfo.AbilityContainer);
	CardAbility->Setup(DropInfo.AbilityContainer,DropInfo.DropTarget,CardAbilityPreset,Card);
	return CardAbility;
}
