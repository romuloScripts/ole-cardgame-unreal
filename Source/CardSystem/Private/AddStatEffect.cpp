// Fill out your copyright notice in the Description page of Project Settings.


#include "AddStatEffect.h"
#include "StatComponent.h"

void UAddStatEffect::NativeApplyEffect(UObject* DropTarget, UObject* TriggerTarget)
{
	Super::NativeApplyEffect(DropTarget, TriggerTarget);
	const auto TargetActor = Cast<AActor>(DropTarget);
	const auto TargetComponent = TargetActor ? TargetActor->GetComponentByClass<UStatComponent>() : nullptr;
	if(TargetComponent) TargetComponent->AddStat(NewStat);
}
