// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHighlight.h"

void UGridHighlight::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UGridHighlight::Hover_Implementation()
{
	if(GetVisibility() != ESlateVisibility::HitTestInvisible) return;
	StopAllAnimations();
	PlayAnimation(Anim_HoverIn);
}

void UGridHighlight::Unhover_Implementation()
{
	if(GetVisibility() != ESlateVisibility::HitTestInvisible) return;
	StopAllAnimations();
	PlayAnimation(Anim_HoverOut);
}

void UGridHighlight::Active_Implementation(const bool Value)
{
	SetVisibility(Value ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	PlayAnimation(Anim_Idle);
}

void UGridHighlight::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	if(IsAnimationPlaying(Anim_HoverOut)) return;
	if(Animation == Anim_HoverIn) PlayAnimation(Anim_HoverIdle,0,0,EUMGSequencePlayMode::PingPong,1,true);
}
