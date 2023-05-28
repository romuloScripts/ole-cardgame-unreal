// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHandWidgetBase.h"

#include "Components/CanvasPanelSlot.h"

void UCardInHandWidgetBase::PlayDrawCard()
{
	StopAllAnimations();
	PlayAnimation(Anim_Draw);
}

void UCardInHandWidgetBase::PlayRemove()
{
	StopAllAnimations();
	PlayAnimation(Anim_Remove);
}

void UCardInHandWidgetBase::SetDefaultZOrder(const int Value)
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	if(CanvasSlot == nullptr) return;
	DefaultZOrder = Value;
	if(!CurrentZoomIn) CanvasSlot->SetZOrder(Value);
}

void UCardInHandWidgetBase::SetCarPos(const FVector2D& Pos) const
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	if(CanvasSlot == nullptr) return;
	CanvasSlot->SetPosition(Pos);
}

void UCardInHandWidgetBase::SetSize(const FVector2D& CardsSize)
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	if(CanvasSlot == nullptr) return;
	CanvasSlot->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
	CanvasSlot->SetSize(CardsSize);
	CanvasSlot->SetAlignment(FVector2D(0.5f,0.5f));
}

void UCardInHandWidgetBase::PutCardInFront(bool ZoomIn)
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	if(CanvasSlot == nullptr) return;
	if(ZoomIn && !CurrentZoomIn)
	{
		CurrentZoomIn = true;
		CanvasSlot->SetZOrder(9999);
	}else if(!ZoomIn && CurrentZoomIn)
	{
		CurrentZoomIn = false;
		CanvasSlot->SetZOrder(DefaultZOrder);
	}
}

void UCardInHandWidgetBase::AnimRemoveEnd()
{
	OnRemoveAnimEnd.Broadcast(this);
}

void UCardInHandWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	CardRemoveAnimEndEvent.BindDynamic(this,&UCardInHandWidgetBase::AnimRemoveEnd);
	BindToAnimationFinished(Anim_Remove,CardRemoveAnimEndEvent);
}
