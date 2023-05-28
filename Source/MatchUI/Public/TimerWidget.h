#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"
#include "TimerWidget.generated.h"

class UTextBlock;
class AMatchGameState;

UCLASS()
class MATCHUI_API UTimerWidget : public UColorContainer
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumHalves = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MatchMaxMinutes = 90;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MatchTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MinuteText;

	UFUNCTION(BlueprintCallable)
	void UpdateTimer();

	virtual void NativeConstruct() override;

private:

	UPROPERTY()
	AMatchGameState* GameState;
};
