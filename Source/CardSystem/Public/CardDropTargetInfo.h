#pragma once
#include "AbilityContainer.h"
#include "CardDropTargetInfo.generated.h"

USTRUCT(BlueprintType)
struct FCardDropTargetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	UAbilityContainer* AbilityContainer;

	UPROPERTY(BlueprintReadWrite)
	UObject* DropTarget;
};
