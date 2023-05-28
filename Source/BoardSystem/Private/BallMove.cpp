// Fill out your copyright notice in the Description page of Project Settings.


#include "BallMove.h"

bool UBallMove::TargetIsValid(AActor* Target)
{
	return Super::TargetIsValid(Target) && InPossessOfBall();
}
