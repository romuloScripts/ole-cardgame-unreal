#include "CardSelectTarget.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

TArray<UObject*> UCardSelectTarget::GetSelectionCandidates_Implementation()
{
	return TArray<UObject*>();
}

bool UCardSelectTarget::IsBoardTarget() const
{
	return GetTargetSelectWidget() == nullptr;
}

TSubclassOf<UUserWidget> UCardSelectTarget::GetTargetSelectWidget_Implementation() const
{
	return nullptr;
}

TArray<FCardDropTargetInfo> UCardSelectTarget::GetTargets()
{
	return SelectedTargets;
}

void UCardSelectTarget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCardSelectTarget, SelectedTargets);
	DOREPLIFETIME(UCardSelectTarget, TargetAmount);
	DOREPLIFETIME(UCardSelectTarget, CandidatesAmount);
}

bool UCardSelectTarget::AllowSelection_Implementation(UObject* Selection)
{
	return false;
}

void UCardSelectTarget::AddSelection_Implementation(UObject* Selection)
{
	
}

void UCardSelectTarget::RemoveSelection_Implementation(UObject* Selection)
{
	
}

bool UCardSelectTarget::SelectionCompleted_Implementation()
{
	return SelectedTargets.Num() >= TargetAmount;
}


