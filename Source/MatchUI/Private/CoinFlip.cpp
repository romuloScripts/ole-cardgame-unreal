// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinFlip.h"

void UCoinFlip::PlayCoinFlip(bool FirstPlayer)
{
	First = FirstPlayer;
	OnUpdateFirst(First);
	PlayAnimation(AnimCoinFlip);
}
