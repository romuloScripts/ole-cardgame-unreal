#include "Card.h"
#include "Net/UnrealNetwork.h"
#include "CardSelectTarget.h"
#include "CardDropTargetInfo.h"
#include "CardFunctionLibrary.h"
#include "DeckFunctionLibrary.h"

void UCard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCard, Preset);
	DOREPLIFETIME(UCard, CardId);
	DOREPLIFETIME(UCard, OwnerPlayer);
}

void UCard::Setup(UCardPreset* CardPreset, APlayerState* Owner)
{
	OwnerPlayer = Owner;
	CardId = GetUniqueID();
	Preset = CardPreset;
}

UCardPreset* UCard::GetPreset() const
{
	return Preset;
}

int32 UCard::GetCardId() const
{
	return CardId;
}

bool UCard::IsTrap() const
{
	return Preset->CardType == ECardType::Trap;
}

bool UCard::IsUnit() const
{
	return UCardFunctionLibrary::IsUnitCard(Preset);
}

bool UCard::TargetRequired() const
{
	if(const auto Target = Preset->Target;
		Target != nullptr && Cast<UCardSelectTarget>(Target))
	{
		return true;
	}
	return false;
}

bool UCard::BoardTargetRequired() const
{
	if(!TargetRequired()) return false;
	const auto Target = Preset->Target;
	const auto SelectTarget = Cast<UCardSelectTarget>(Target);
	return SelectTarget && SelectTarget->IsBoardTarget();
}

APlayerState* UCard::GetOwnerPlayer() const
{
	return OwnerPlayer; 
}

UCardTarget* UCard::GetCardTarget(UObject* TargetOuter)
{
	const auto CardTarget = Cast<UCardTarget>(DuplicateObject(Preset->Target,TargetOuter));
	CardTarget->ClearFlags(RF_WasLoaded);
	CardTarget->ClearFlags(RF_LoadCompleted);
	CardTarget->Setup(this);
	return CardTarget;
}

TArray<FCardDropTargetInfo> UCard::GetTargetContainers(UObject* TargetOuter)
{
	if(!Preset->Target) return TArray<FCardDropTargetInfo>();
	UCardTarget* CardTarget = GetCardTarget(TargetOuter);
	return CardTarget->GetTargets();
}
