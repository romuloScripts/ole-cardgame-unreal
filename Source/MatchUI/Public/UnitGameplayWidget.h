// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardContainer.h"
#include "SetupSoccerActor.h"
#include "UnitGameplayWidget.generated.h"

class AUnitActor;
class ASoccerActor;
class UStatIconWidget;
class UImage;
class UVerticalBox;
class USizeBox;
class UTrapIconWidget;
class UYellowCardWidget;
class UTextBlock;
class UUnitWidget;
struct FGameplayTag;
enum class EHoverType : uint8;
enum class ETrapAbilityChange : uint8;
enum class EDamageType : uint8;
enum class EMoveType : uint8;
enum class EMoveDirection : uint8;

UCLASS()
class MATCHUI_API UUnitGameplayWidget : public UCardContainer, public ISetupSoccerActor
{
	GENERATED_BODY()
public:
	
	virtual void Setup_Implementation(ASoccerActor* UnitActor) override;
	
	UFUNCTION(BlueprintCallable)
	void ActiveInteraction(bool Value);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void Hover(EHoverType HoverType);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void Unhover();
	
	UFUNCTION(BlueprintCallable)
	void SetPoints(int Points);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void LocomotionChanged(bool IsMoving);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void MoveApplied(EMoveType Move,EMoveDirection Direction);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void MoveReceived(EMoveType Move,EMoveDirection Direction,bool Success);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnReceivePoint(int Amount);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnTakeDamage(ASoccerActor* SoccerActor,EDamageType DamageType,int Damage,AActor* DamageCauser);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnForceTakeDamage(int Damage);

	UFUNCTION(BlueprintCallable)
	void Active(bool Value);

	UFUNCTION(BlueprintCallable)
	void RedCard(AUnitActor* UnitActor);
	
	UFUNCTION(BlueprintCallable)
	void ActiveYellowCard(bool Value);

	UFUNCTION(BlueprintCallable)
	void AddTrap(ETrapAbilityChange AbilityChange);

	UFUNCTION(BlueprintCallable)
	bool ShowTrapCard();

	UFUNCTION(BlueprintCallable)
	bool ShowCardPreview();
	
	void UpdateMargin() const;

	UFUNCTION(BlueprintCallable)
	void AddStat(FGameplayTag NewStat);
	
	UFUNCTION(BlueprintCallable)
	void RemoveStat(FGameplayTag StatToRemove);

	UFUNCTION(BlueprintCallable)
	void AddBarrier(bool Add);

	UFUNCTION(BlueprintCallable)
	void AddTough(bool Add);

	UFUNCTION(BlueprintCallable)
	void LevelUp(int NewLevel);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdateLevel();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdatePoints(int NewPoints);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<UStatIconWidget> IconClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default, meta = (BindWidget, UIMin = "0", UIMax = "1.0"))
	float DisabledOpacity = 0.4f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	float Margin = -12;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUnitWidget* BP_Unit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PointsText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UYellowCardWidget* YellowCard;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTrapIconWidget* TrapIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Stats_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* PointsIndicator;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Trap_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* Stats_VerticalBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BarrierIconBG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BarrierGlow;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PointsBGTough;

	UPROPERTY(BlueprintReadWrite)
	AUnitActor* Unit;
};
