#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DrawCardOperation.generated.h"

class UCard;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class CARDSYSTEM_API UDrawCardOperation : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,meta = (ExposeOnSpawn="true"))
	APlayerState* PlayerState;

	UPROPERTY(BlueprintReadWrite,meta = (ExposeOnSpawn="true"))
	TArray<UCard*> CardsToDraw;

	UPROPERTY(BlueprintReadWrite,meta = (ExposeOnSpawn="true"))
	TArray<UCard*> CardsToRemove;
};
