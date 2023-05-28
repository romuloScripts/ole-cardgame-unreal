// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UStatComponent, StatsContainer);
}

bool UStatComponent::ContainsStat(const FGameplayTag& Tag) const
{
	return StatsContainer.HasTag(Tag);
}

void UStatComponent::AddStat(const FGameplayTag Tag)
{
	if(ContainsStat(Tag)) return;
	StatsContainer.AddTag(Tag);
	OnAddStatEvent(Tag);
}

void UStatComponent::OnAddStatEvent_Implementation(const FGameplayTag Tag)
{
	OnStatAdded.Broadcast(Tag);
}

FGameplayTagContainer UStatComponent::GetStats()
{
	return StatsContainer;
}

