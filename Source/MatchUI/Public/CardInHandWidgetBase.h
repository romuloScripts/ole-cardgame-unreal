// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CardInHandWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardInHanOnHover, UCardInHandWidgetBase*, CardInHand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardInHanOnRemoveAnimEnd, UCardInHandWidgetBase*, CardInHand);

UCLASS(Abstract)
class MATCHUI_API UCardInHandWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Draw;

	UPROPERTY(BlueprintReadOnly,Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim_Remove;

	UPROPERTY(BlueprintReadOnly)
	int DefaultZOrder;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FCardInHanOnHover OnHoverIn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FCardInHanOnHover OnHoverOut;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FCardInHanOnRemoveAnimEnd OnRemoveAnimEnd;

	UFUNCTION(BlueprintCallable)
	void PlayDrawCard();

	UFUNCTION(BlueprintCallable)
	void PlayRemove();

	UFUNCTION(BlueprintCallable)
	void SetDefaultZOrder(const int Value);

	UFUNCTION(BlueprintCallable)
	void SetCarPos(const FVector2D& Pos) const;

	UFUNCTION(BlueprintCallable)
	void SetSize(const FVector2D& CardsSize);

protected:

	UPROPERTY(BlueprintReadOnly)
	bool CurrentZoomIn;

	UPROPERTY()
	FWidgetAnimationDynamicEvent CardRemoveAnimEndEvent;

	UFUNCTION(BlueprintCallable)
	void PutCardInFront(bool ZoomIn);
	
	UFUNCTION()
	void AnimRemoveEnd();

	virtual void NativeConstruct() override;
};
