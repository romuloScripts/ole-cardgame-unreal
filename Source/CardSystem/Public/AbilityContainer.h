#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityContainer.generated.h"

class UCard;
class UCardAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeTrapAbility, ETrapAbilityChange, Value, UCard*, Card);

UCLASS()
class CARDSYSTEM_API UAbilityContainer : public UObject
{
	GENERATED_BODY()
public:
		
	UFUNCTION()
	void Setup(APlayerState* State);
	
	UFUNCTION(BlueprintCallable)
	void AddAbility(UCardAbility* CardAbility);

	UFUNCTION(BlueprintCallable)
	void Remove(UCardAbility* CardAbility);

	UFUNCTION(BlueprintCallable)
	APlayerState* GetPlayerState() const;

	UFUNCTION(BlueprintCallable)
	void TrapActivated(UCard* Card);

	UFUNCTION(BlueprintCallable)
	class UCardPreset* GetTrapCard();

	UFUNCTION(BlueprintCallable)
	void RemoveAllEffects();

	UPROPERTY(BlueprintCallable)
	FOnChangeTrapAbility OnChangeTrapEffect;

	UFUNCTION(BlueprintCallable)
	bool ContainsTrapAbility() const;
	
protected:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	TArray<UCardAbility*> Abilities;

	UPROPERTY(BlueprintReadWrite)
	APlayerState* PlayerState;
};
