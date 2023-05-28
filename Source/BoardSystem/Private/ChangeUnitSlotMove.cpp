// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeUnitSlotMove.h"

#include "BoardSlot.h"
#include "BoardFunctionLibrary.h"

bool UChangeUnitSlotMove::TargetIsValid(AActor* Target)
{
	if(!Super::TargetIsValid(Target)) return false;
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	if(TargetSlot == nullptr) return false;
	return TargetSlot != UnitActor->CurrentSlot && UnitActor->GetPlayerId() == TargetSlot->PlayerId && TargetSlot->GridId.X == UnitActor->CurrentSlot->GridId.X;
}

void UChangeUnitSlotMove::Move(AActor* Target)
{
	const auto TargetSlot = Cast<ABoardSlot>(Target);
	const auto OldSlot = UnitActor->CurrentSlot;
	const bool UpDir = TargetSlot->GridId.Y > OldSlot->GridId.Y;
	const auto OldUnit = TargetSlot->AttachedUnit;
	TargetSlot->AttachUnit(UnitActor);
	UnitActor->MoveToSlot(TargetSlot);
	UnitActor->OnAnimFinished.AddDynamic(this,&UChangeUnitSlotMove::EndMove);
	OldSlot->AttachUnit(nullptr);
			
	if(OldUnit)
	{
		UBoardFunctionLibrary::MoveUnitsToDir(OldUnit,UpDir);
	}
}