// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterUseState.h"
#include "AbilityEffect.h"
#include "CardAbility.h"

void UAfterUseState::Setup(UCardAbility* CardAbility)
{
	Ability = CardAbility;
	Ability->Effect->OnUse.AddDynamic(this,&UAfterUseState::Used);
	PostSetup();
}

void UAfterUseState::Used()
{
	AbilityUsed();
	AbilityWasUsed = true;
}

void UAfterUseState::RemoveAfterUseState_Implementation()
{
}

void UAfterUseState::PostSetup_Implementation()
{
	
}

void UAfterUseState::RemoveAbility() const
{
	Ability->Remove();
}

void UAfterUseState::RemoveEffect()
{
	Ability->Effect->Remove();
}

void UAfterUseState::AbilityUsed_Implementation()
{
}
