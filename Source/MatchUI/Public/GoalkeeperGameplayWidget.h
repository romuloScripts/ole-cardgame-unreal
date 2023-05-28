// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GoalkeeperContainer.h"
#include "SetupSoccerActor.h"

#include "GoalkeeperGameplayWidget.generated.h"

enum class EDamageType : uint8;
class ASoccerActor;
class UTrapIconWidget;
class AGoalkeeperActor;
UCLASS()
class MATCHUI_API UGoalkeeperGameplayWidget : public UGoalkeeperContainer, public ISetupSoccerActor
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTrapIconWidget* TrapIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PointsText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* GoalkeeperBG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* BPGoalkeeper;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget, UIMin = "0", UIMax = "1.0"))
	float DisabledOpacity = 0.4f;

	UPROPERTY(BlueprintReadWrite)
	AGoalkeeperActor* Goalkeeper; 

	virtual void Setup_Implementation(ASoccerActor* UnitActor) override;

	UFUNCTION(BlueprintCallable)
	bool ShowTrapCard();

	UFUNCTION(BlueprintCallable)
	void AddTrap(ETrapAbilityChange AbilityChange);

	UFUNCTION(BlueprintCallable)
	void SetPoints(int Points);

	UFUNCTION(BlueprintCallable)
	void SetFlip(bool Flip);
	
	UFUNCTION(BlueprintCallable)
	void Active(bool Value);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnReceivePoint(int Amount);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnTakeDamage(ASoccerActor* SoccerActor,EDamageType DamageType,int Damage,AActor* DamageCauser);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnForceTakeDamage(int Damage);
};
