
#include "AbilityContainer.h"
#include "CardAbility.h"
#include "Card.h"
#include "GameStateEnums.h"

void UAbilityContainer::Setup(APlayerState* State)
{
	PlayerState = State;
}

void UAbilityContainer::AddAbility(UCardAbility* CardAbility)
{
	const bool ContainsTrap = ContainsTrapAbility();
	Abilities.Add(CardAbility);
	const bool NewContainsTrap = ContainsTrapAbility();
	if(ContainsTrap != NewContainsTrap)
	{
		OnChangeTrapEffect.Broadcast(ETrapAbilityChange::Add,CardAbility->OwnerCard);
	}
}

void UAbilityContainer::Remove(UCardAbility* CardAbility)
{
	const bool ContainsTrap = ContainsTrapAbility();
	Abilities.Remove(CardAbility);
	const bool NewContainsTrap = ContainsTrapAbility();
	if(ContainsTrap != NewContainsTrap) OnChangeTrapEffect.Broadcast(ETrapAbilityChange::Remove,CardAbility->OwnerCard);
	CardAbility->ConditionalBeginDestroy();
}

APlayerState* UAbilityContainer::GetPlayerState() const
{
	return PlayerState;
}

void UAbilityContainer::TrapActivated(UCard* Card)
{
	//GetPlayerState()->InvokeOnTrapCardActivated(Card);
	OnChangeTrapEffect.Broadcast(ETrapAbilityChange::Activated,Card);
}

void UAbilityContainer::RemoveAllEffects()
{
	for (auto item : Abilities)
	{
		item->ConditionalBeginDestroy();
	}
	Abilities.Empty();
}

UCardPreset* UAbilityContainer::GetTrapCard()
{
	for (const auto Item : Abilities)
	{
		if(Item->IsTrapAbility())
		{
			return Item->OwnerCard->GetPreset();
		}
	}
	return nullptr;
}

bool UAbilityContainer::ContainsTrapAbility() const
{
	if(Abilities.IsEmpty()) return false;
	for (const auto Item : Abilities)
	{
		if(Item->IsTrapAbility())
		{
			return true;
		}
	}
	return false;
}
