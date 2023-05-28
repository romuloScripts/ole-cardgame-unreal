#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardTargetBase.h"
#include "CardTarget.generated.h"


struct FCardDropTargetInfo;
class UCard;

UCLASS(Blueprintable,BlueprintType,Abstract,EditInlineNew)
class CARDSYSTEM_API UCardTarget : public UCardTargetBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void Setup(UCard* OwnerCard);

	UFUNCTION(BlueprintCallable)
	virtual TArray<FCardDropTargetInfo> GetTargets();
	
	UFUNCTION(BlueprintCallable)
	UCard* GetCard() const;

	UFUNCTION(BlueprintCallable)
	APlayerState* GetPlayer() const;

protected:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<FCardDropTargetInfo> RequestTargets();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override { return true; }

	UPROPERTY(Replicated,BlueprintReadWrite)
	UCard* Card;
};
