
#include "AbilityEffect.h"

void UAbilityEffect::ApplyEffect_Implementation(UObject* DropTarget,UObject* TriggerTarget)
{
}

void UAbilityEffect::RemoveEffect_Implementation(UObject* DropTarget,UObject* TriggerTarget)
{
}

void UAbilityEffect::NativeApplyEffect(UObject* DropTarget, UObject* TriggerTarget)
{
	
}

void UAbilityEffect::Use(UObject* DropTarget,UObject* TriggerTarget)
{
	DTarget = DropTarget;
	TTarget = TriggerTarget;
	ApplyEffect(DropTarget,TriggerTarget);
	NativeApplyEffect(DropTarget,TriggerTarget);
	OnUse.Broadcast();
}

void UAbilityEffect::Remove()
{
	RemoveEffect(DTarget,TTarget);
}
