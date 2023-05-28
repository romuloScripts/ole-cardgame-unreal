// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTrigger.h"

#include "CardAbility.h"

void UAbilityTrigger::Setup(UCardAbility* CardAbility)
{
	Ability = CardAbility;
	Active();
}

void UAbilityTrigger::Remove()
{
	RemoveObserveTriggerCondition();
}

void UAbilityTrigger::Active()
{
	ObserveTriggerCondition();
}

void UAbilityTrigger::TriggerAbility(UObject* TriggerTarget)
{
	if(MaxTriggers > 0)
	{
		if(TotalTriggers>= MaxTriggers)
		{
			return;
		}
		TotalTriggers++;
	}
	Ability->TriggerAbility(TriggerTarget);
}

void UAbilityTrigger::RemoveObserveTriggerCondition_Implementation()
{
}

void UAbilityTrigger::ObserveTriggerCondition_Implementation()
{
}
