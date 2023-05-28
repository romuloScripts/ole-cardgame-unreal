#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionInfoWidget.generated.h"


UCLASS()
class MATCHUI_API UActionInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetAction(int Cost, const FText& Action, bool Blocked);
};
