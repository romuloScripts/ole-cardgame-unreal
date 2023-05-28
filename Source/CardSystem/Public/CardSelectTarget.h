// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTarget.h"
#include "CardDropTargetInfo.h"
#include "UObject/Object.h"
#include "CardSelectTarget.generated.h"

class UCardTargetWidget;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,Abstract)
class CARDSYSTEM_API UCardSelectTarget : public UCardTarget
{
	GENERATED_BODY()
public:

	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	int TargetAmount=1;
	
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	int CandidatesAmount=1;
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	TArray<FCardDropTargetInfo> SelectedTargets;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<UObject*> GetSelectionCandidates();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool AllowSelection(UObject* Selection);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AddSelection(UObject* Selection);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RemoveSelection(UObject* Selection);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool SelectionCompleted();

	UFUNCTION()
	bool IsBoardTarget() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TSubclassOf<UUserWidget> GetTargetSelectWidget() const;
	
	virtual TArray<FCardDropTargetInfo> GetTargets() override;

protected:

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
};
