// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayedWidget.h"

#include "BoardFunctionLibrary.h"
#include "CardTargetWidget.h"
#include "CardWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "CardSystem/Public/Card.h"
#include "CardSystem/Public/CardSelectTarget.h"
#include "Components/RichTextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Match/Public/MatchPlayerState.h"


void UCardPlayedWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	AnimEndEventIn.BindDynamic(this,&UCardPlayedWidget::FinishedIn);
	AnimEndEventOut.BindDynamic(this,&UCardPlayedWidget::FinishedOut);
}

void UCardPlayedWidget::SetUser(AMatchPlayerState* Player, bool IsOpponent)
{
	if(PlayerState == Player) return;
	Super::SetUser(Player, IsOpponent);
	Opponent = IsOpponent;
	PlayerState->OnCardUsed.AddDynamic(this,&UCardPlayedWidget::OnCardUsed);
	if(!Opponent)
	{
		PlayerState->OnWaitCardTargets.AddDynamic(this,&UCardPlayedWidget::OnWaitCardTargets);
		PlayerState->OnCancelWaitCardTargets.AddDynamic(this,&UCardPlayedWidget::OnCancelWaitCardTargets);
	}
}

void UCardPlayedWidget::OnCardUsed(UCard* NewCard)
{
	if(WaitConfirm && NewCard == CurrentCard)
	{
		CardUsed = true;
		PlayCardOut();
	}else
	{
		Clear();
		CardUsed = true;
		PlayCard(NewCard);
	}
}

void UCardPlayedWidget::OnWaitCardTargets(UCard* NewCard,UCardSelectTarget* CardTarget)
{
	Clear();
	WaitConfirm = true;
	PlayCard(NewCard);
}

void UCardPlayedWidget::OnCancelWaitCardTargets(UCard* NewCard)
{
	if(!WaitConfirm) return;
	HideInfo();
}

void UCardPlayedWidget::PlayCard(UCard* NewCard)
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CurrentCard = NewCard;
	UpdateCard(NewCard);
	if(!Opponent)
	{
		Description->SetText(NewCard->GetPreset()->PlacementInfo);
		BindAnimIn();
		PlayAnimation(Anim_In);
	}else
	{
		Description->SetText(NewCard->IsTrap() ? TrapCardDescription : FText::GetEmpty());
		BindAnimIn();
		PlayAnimation(NewCard->IsTrap() ? Anim_In_Opponent_Trap : Anim_In_Opponent);
	}
}

void UCardPlayedWidget::OnPlayAnimEnd()
{
	if(Opponent || !WaitConfirm)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UCardPlayedWidget::PlayCardOut, DisplayTime, false);
	}else
	{
		Card->PlayHighligh();
	}
}

void UCardPlayedWidget::PlayCardOut()
{
	WaitConfirm = false;
	RemoveTargetWidget();
	if(!CurrentCard) return;
	BindAnimOut();
	PlayAnimation(CurrentCard->IsTrap() && Opponent ? Anim_Out_Opponent_Trap : Anim_Out);
}



void UCardPlayedWidget::Clear()
{
	if(CardUsed) FinishedCardUsed();
	RemoveTargetWidget();
	CardUsed = false;
	CurrentCard = nullptr;
	WaitConfirm = false;
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	UnbindAnimIn();
	UnbindAnimOut();
	StopAllAnimations();
}

void UCardPlayedWidget::HideInfo()
{
	Clear();
	SetVisibility(ESlateVisibility::Hidden);
}

void UCardPlayedWidget::UpdateCard(UCard* NewCard)
{
	const auto NewLevel = UBoardFunctionLibrary::GetUnitNextLevelByPreset(NewCard->GetPreset(),PlayerState);
	Card->UpdateCard(NewCard->GetPreset(),NewLevel);
}

void UCardPlayedWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(PlayerState == nullptr) return;

	UpdateTargetWidget();
	
	if(PlayerState->GetMoveState() == ETurnMoveState::None && WaitConfirm)
	{
		HideInfo();
	}
}

void UCardPlayedWidget::FinishedIn()
{
	if(CurrentCard == nullptr) return;
	OnPlayAnimEnd();
}

void UCardPlayedWidget::FinishedOut()
{
	if(CurrentCard == nullptr) return;
	HideInfo();
}

void UCardPlayedWidget::BindAnimIn()
{
	BindToAnimationFinished(Anim_In,AnimEndEventIn);
	BindToAnimationFinished(Anim_In_Opponent,AnimEndEventIn);
	BindToAnimationFinished(Anim_In_Opponent_Trap,AnimEndEventIn);
}

void UCardPlayedWidget::BindAnimOut()
{
	BindToAnimationFinished(Anim_Out,AnimEndEventOut);
	BindToAnimationFinished(Anim_Out_Opponent_Trap,AnimEndEventOut);
}

void UCardPlayedWidget::UnbindAnimIn()
{
	UnbindFromAnimationFinished(Anim_In,AnimEndEventIn);
	UnbindFromAnimationFinished(Anim_In_Opponent,AnimEndEventIn);
	UnbindFromAnimationFinished(Anim_In_Opponent_Trap,AnimEndEventIn);
}

void UCardPlayedWidget::UnbindAnimOut()
{
	UnbindFromAnimationFinished(Anim_Out,AnimEndEventOut);
	UnbindFromAnimationFinished(Anim_Out_Opponent_Trap,AnimEndEventOut);
}

void UCardPlayedWidget::CreateTargetWidget()
{
	if(!PlayerState->GetCardTarget()) return;
	const auto Target =PlayerState->GetCardTarget();
	TargetWidget = CreateWidget<UCardTargetWidget>(TargetWidgetPanel,Target->GetTargetSelectWidget());
	const auto OverlaySlot = Cast<UOverlaySlot>(TargetWidgetPanel->AddChild(TargetWidget));
	OverlaySlot->SetHorizontalAlignment(HAlign_Center);
	OverlaySlot->SetVerticalAlignment(VAlign_Center);
	TargetWidget->Setup(PlayerState,PlayerState->GetCardTarget());
}

void UCardPlayedWidget::RemoveTargetWidget()
{
	if(!TargetWidget) return;
	TargetWidgetPanel->RemoveChild(TargetWidget);
	TargetWidget = nullptr;
}

void UCardPlayedWidget::UpdateTargetWidget()
{
	if(Opponent) return;
	
	if(TargetWidget == nullptr && PlayerState->GetMoveState() == ETurnMoveState::WaitSelectCardTarget && WaitConfirm && PlayerState->GetCardTarget())
	{
		//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, TEXT("CreateTargetWidget"));
		CreateTargetWidget();
	}

	//GEngine->AddOnScreenDebugMessage(0, 0.1, FColor::Green, TEXT("UpdateTargetWidget"));
	if(!PlayerState->GetCardTarget())
	{
		//GEngine->AddOnScreenDebugMessage(0, 0.1, FColor::Red, TEXT("GetCardTarget"));
	}
	if(UGameplayStatics::GetPlayerController(this,0)->WasInputKeyJustReleased(EKeys::RightMouseButton)
		&& PlayerState->GetCardTarget() && !IsPlayingAnimation())
	{
		//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Blue, TEXT("CancelCardTarget"));
		PlayerState->CancelCardTarget();
	}
}

FVector UCardPlayedWidget::GetCardWidgetArrowOriginPos()
{
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(this,Card->GetCachedGeometry(),Card->GetCachedGeometry().GetLocalSize() / 2.0f,PixelPosition,ViewportPosition);
	FVector WorldPosition;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(GetWorld()->GetFirstPlayerController(),PixelPosition,WorldPosition,WorldDirection);
	float T;
	if(FVector Intersection; UKismetMathLibrary::LinePlaneIntersection_OriginNormal(
		WorldPosition, WorldPosition + (WorldDirection * 10000000),FVector::Zero(), FVector::ForwardVector,T,Intersection))
	{
		return Intersection;
	}
	return FVector::Zero();
}




