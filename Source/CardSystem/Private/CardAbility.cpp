#include "CardAbility.h"
#include "AbilityContainer.h"
#include "AbilityEffect.h"
#include "AbilityTrigger.h"
#include "AfterUseState.h"
#include "Card.h"
#include "CardAbilityPreset.h"

void UCardAbility::Setup(UAbilityContainer* Container, UObject* Target, const UCardAbilityPreset* CardAbilityPreset,UCard* Card)
{
	if(Card)
	{
		OwnerCard = Card;
	}
	OwnerContainer = Container;
	OwnerContainer->AddAbility(this);
	DropTarget = Target ? Target : OwnerContainer->GetOuter();
	Effect = DuplicateObject(Cast<UAbilityEffect>(CardAbilityPreset->Effect),this);
	if(CardAbilityPreset->AfterUseState)
	{
		AfterUseState = DuplicateObject(Cast<UAfterUseState>(CardAbilityPreset->AfterUseState),this);
		AfterUseState->Setup(this);
	}
	Trigger = DuplicateObject(Cast<UAbilityTrigger>(CardAbilityPreset->Trigger),this);
	Trigger->Setup(this);
}

void UCardAbility::TriggerAbility(UObject* TriggerTarget)
{
	if(IsTrapAbility())
	{
		OwnerContainer->TrapActivated(OwnerCard);
	}
	Effect->Use(DropTarget,TriggerTarget);
}

bool UCardAbility::IsTrapAbility()
{
	return OwnerCard && OwnerCard->IsTrap();
}

APlayerState* UCardAbility::GetPlayerState() const
{
	return OwnerContainer->GetPlayerState();
}

void UCardAbility::Remove()
{
	if(AfterUseState) AfterUseState->RemoveAfterUseState();
	Trigger->Remove();
	Effect->Remove();
	if(OwnerContainer) OwnerContainer->Remove(this);
}


