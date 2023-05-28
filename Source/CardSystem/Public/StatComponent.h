// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatAdded,FGameplayTag, NewTag);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDSYSTEM_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	bool ContainsStat(const FGameplayTag& Tag) const;

	UFUNCTION(BlueprintCallable)
	void AddStat(const FGameplayTag Tag);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	FGameplayTagContainer GetStats();
	
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category="Button|Event")
	FOnStatAdded OnStatAdded;

protected:

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Replicated)
	FGameplayTagContainer StatsContainer = FGameplayTagContainer();

	UFUNCTION(BlueprintCallable,Reliable,NetMulticast)
	void OnAddStatEvent(const FGameplayTag NewStat);
};
