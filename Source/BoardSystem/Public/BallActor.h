#pragma once

#include "BoardInteractable.h"
#include "Components/WidgetComponent.h"
#include "Components/TimelineComponent.h"
#include "BallActor.generated.h"

class ASoccerActor;
class UMove;
class AUnitActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBallAnimFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHover,bool,Value);

UCLASS()
class BOARDSYSTEM_API ABallActor : public AActor, public IBoardInteractable
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* MovementAnimCurve;

	UPROPERTY(EditAnywhere,BlueprintReadWrite  = Default)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(Replicated,BlueprintReadWrite)
	ASoccerActor* AttachedActor;
	
	UPROPERTY()
	FTimeline Timeline;

	UPROPERTY()
	FVector LastPos;

	UPROPERTY()
	FOnBallAnimFinished OnAnimFinished;

	UPROPERTY()
	FOnHover OnHover;
	
	UPROPERTY(BlueprintReadWrite)
	ASoccerActor* TargetActor;

	ABallActor();

	UFUNCTION(NetMulticast, Reliable,BlueprintCallable)
	void MoveToActor(ASoccerActor* SoccerActor);

	UFUNCTION(BlueprintCallable)
	void StartMovementAnimation();

	UFUNCTION()
	void SetMovementAnimValue(float Value);

	UFUNCTION()
	void EndMovementAnimation();

	UFUNCTION(NetMulticast,Reliable,BlueprintCallable)
	void AttachToSoccerActor(ASoccerActor* SoccerActor, bool SetPos);

	UFUNCTION()
	void AttachToSoccerActorLocal(ASoccerActor* SoccerActor, bool SetPos);
	
	virtual void Select_Implementation(const bool Value) override;
	
	virtual void Hover_Implementation(EHoverType HoverType) override;
	
	virtual void Unhover_Implementation() override;

	virtual int GetOwnerPlayerId_Implementation() override;
	
	virtual bool InteractionAllowed_Implementation(int PlayerId) override;

	virtual void TryMoveTo_Implementation(AActor* Target) override;
	
	virtual UMove* GetMove_Implementation(AActor* Target) override;

	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
