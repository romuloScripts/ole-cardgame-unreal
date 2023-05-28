// Fill out your copyright notice in the Description page of Project Settings.


#include "CardBackInHand.h"

#include "CardBackWidget.h"

void UCardBackInHand::SetupCardBack(UCardBackPreset* Preset, UColorPreset* Color,bool UseReserveColor)
{
	CardBack->UpdateCardBack(Preset);
	CardBack->UpdateColorAndReserve(Color,UseReserveColor);
}
