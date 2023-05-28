// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardDropTargetInfo.h"
#include "UObject/Object.h"
#include "Card.generated.h"

class UCardTarget;
class UCardAbilityPreset;
class UCardPreset;

UCLASS(BlueprintType)
class CARDSYSTEM_API UCard : public UObject
{
	GENERATED_BODY()
public:

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override { return true; }

	UFUNCTION(BlueprintCallable)
	void Setup(UCardPreset* CardPreset, APlayerState* Owner);

	UFUNCTION(BlueprintCallable)
	UCardPreset* GetPreset() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCardId() const;

	UFUNCTION(BlueprintCallable)
	bool IsTrap() const;

	UFUNCTION(BlueprintCallable)
	bool IsUnit() const;

	UFUNCTION(BlueprintCallable)
	bool TargetRequired() const;

	UFUNCTION(BlueprintCallable)
	bool BoardTargetRequired() const;

	UFUNCTION(BlueprintCallable)
	APlayerState* GetOwnerPlayer() const;

	UFUNCTION(BlueprintCallable)
	UCardTarget* GetCardTarget(UObject* TargetOuter);

	UFUNCTION()
	TArray<FCardDropTargetInfo> GetTargetContainers(UObject* TargetOuter);

protected:
	UPROPERTY(BlueprintReadWrite,Replicated)
	UCardPreset* Preset;

	UPROPERTY(BlueprintReadWrite,Replicated)
	int32 CardId;

	UPROPERTY(BlueprintReadWrite,Replicated)
	APlayerState* OwnerPlayer;
};

USTRUCT(BlueprintType)
struct FCardWithLevel
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardPreset* CardPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(BlueprintReadWrite)
	UCard* Card;
};
