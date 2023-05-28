// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "UObject/Object.h"
#include "CardDragDropOperation.generated.h"

class UCard;

UCLASS(BlueprintType)
class MATCHUI_API UCardDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	UCard* Card;
};
