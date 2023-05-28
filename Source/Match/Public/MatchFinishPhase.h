#pragma once

#include "CoreMinimal.h"
#include "Phase.h"
#include "MatchFinishPhase.generated.h"

/**
 * 
 */
UCLASS()
class MATCH_API UMatchFinishPhase : public UPhase
{
	GENERATED_BODY()
public:
	
	virtual void OnBegin(const FGameContext& Context) override;

	virtual bool EndIf() override;
};
