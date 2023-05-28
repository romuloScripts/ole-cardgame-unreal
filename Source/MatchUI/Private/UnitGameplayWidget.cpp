#include "UnitGameplayWidget.h"
#include "BoardFunctionLibrary.h"
#include "GameTags.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/VerticalBoxSlot.h"
#include "UnitActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MatchHUDBase.h"
#include "MatchPlayerController.h"
#include "RulesFunctionLibrary.h"
#include "StatComponent.h"
#include "StatIconWidget.h"
#include "TrapIconWidget.h"
#include "UnitWidget.h"
#include "YellowCardWidget.h"

void UUnitGameplayWidget::Setup_Implementation(ASoccerActor* UnitActor)
{
	Unit = Cast<AUnitActor>(UnitActor);
	UpdateAllPResets(Unit->CardPreset,0,Unit->UniformPreset,Unit->ColorPreset,Unit->UseReserveColor);
	SetPoints(Unit->GetPoints());
	const auto Stats = UBoardFunctionLibrary::GetStatComponent(Unit);
	if(Stats)
	{
		for (const auto Stat : Stats->GetStats())
		{
			AddStat(Stat);
		}
		Stats->OnStatAdded.AddDynamic(this,&ThisClass::AddStat);
	}

	Unit->OnHovered.AddDynamic(this,&ThisClass::Hover);
	Unit->OnUnhovered.AddDynamic(this,&ThisClass::Unhover);
	Unit->OnRedCardReceived.AddDynamic(this,&ThisClass::RedCard);
	Unit->OnChangeYellowCard.AddDynamic(this,&ThisClass::ActiveYellowCard);
	Unit->OnChangeTrapEffect.AddDynamic(this,&ThisClass::AddTrap);
	Unit->OnLevelUp.AddDynamic(this,&ThisClass::LevelUp);
	Unit->OnPointsChanged.AddDynamic(this,&ThisClass::SetPoints);
	Unit->OnChangeActive.AddDynamic(this,&ThisClass::Active);
	Unit->OnLocomotionChanged.AddDynamic(this,&ThisClass::LocomotionChanged);
	Unit->OnMoveApplied.AddDynamic(this,&ThisClass::MoveApplied);
	Unit->OnMoveReceived.AddDynamic(this,&ThisClass::MoveReceived);
	Unit->OnPostTakeDamage.AddDynamic(this,&ThisClass::OnTakeDamage);
	Unit->OnPostForceDamage.AddDynamic(this,&ThisClass::OnForceTakeDamage);
	Unit->OnReceivePoints.AddDynamic(this,&ThisClass::OnReceivePoint);
	BP_Unit->OnRightClick.BindDynamic(this,&ThisClass::ShowCardPreview);
	if(Unit->IsLocal())
	{
		TrapIcon->OnClickTrapIcon.BindDynamic(this,&ThisClass::ShowTrapCard);
	}else
	{
		const auto StatsSlot = Cast<UOverlaySlot>(Stats_SizeBox->Slot);
		StatsSlot->SetHorizontalAlignment(HAlign_Right);
		const auto TrapSlot = Cast<UOverlaySlot>(Trap_SizeBox->Slot);
		TrapSlot->SetHorizontalAlignment(HAlign_Left);
	}
}

void UUnitGameplayWidget::ActiveInteraction(const bool Value)
{
	if(!Value) Unhover();
}

void UUnitGameplayWidget::SetPoints(const int Points)
{
	PointsText->SetText(FText::AsNumber(Points));
	UpdatePoints(Points);
}

void UUnitGameplayWidget::Active(bool Value)
{
	const auto Opacity = FMath::Lerp(DisabledOpacity,1.0f,static_cast<float>(Value));
	BP_Unit->SetRenderOpacity(Opacity);
}

void UUnitGameplayWidget::RedCard(AUnitActor* UnitActor)
{
	SetRenderOpacity(0);
}

void UUnitGameplayWidget::ActiveYellowCard(const bool Value)
{
	if(Value)
	{
		YellowCard->AddYellowCard();
	}else
	{
		YellowCard->RemoveYellowCard();
	}
}

void UUnitGameplayWidget::AddTrap(const ETrapAbilityChange AbilityChange)
{
	switch (AbilityChange) {
		case ETrapAbilityChange::Add: TrapIcon->AddTrap(); break;
		case ETrapAbilityChange::Remove: TrapIcon->RemoveTrap(); break;
		case ETrapAbilityChange::Activated: TrapIcon->ActivateTrap(); break;
	}
}

bool UUnitGameplayWidget::ShowTrapCard()
{
	const auto Player = Cast<AMatchPlayerController>(Unit->GetOwnerPlayerController());
	if(Player && Player->IsLocalController())
	{
		return Player->GetMatchHud()->ShowCardPreview(Unit->GetTrapCard(),Player->PlayerStateRef->PlayerStatus);
	}
	return false;
}

bool UUnitGameplayWidget::ShowCardPreview()
{
	const auto Status = Cast<AMatchPlayerState>(Unit->GetOwnerPlayerState())->PlayerStatus;
	if(const auto Player = URulesFunctionLibrary::GetOnlinePlayerController(this))
	{
		return Player->GetMatchHud()->ShowCardPreview(Unit->CardPreset,Status);
	}
	return false;
}

void UUnitGameplayWidget::UpdateMargin() const
{
	const auto ChildCount = Stats_VerticalBox->GetChildrenCount();
	for(int i =0; i < ChildCount;i++)
	{
		const auto First = ChildCount > 1 && i == 0;
		const auto Last = ChildCount > 1 && i == ChildCount-1;
		const auto Top = First ? 0 : Margin;
		const auto Bottom = Last ? 0 : Margin;
		const auto VerticalSlot = UWidgetLayoutLibrary::SlotAsVerticalBoxSlot(Stats_VerticalBox->GetChildAt(i));
		VerticalSlot->SetPadding(FMargin(Top,0,0,Bottom));
	}
}

void UUnitGameplayWidget::AddStat(FGameplayTag NewStat)
{
	if(Stats_VerticalBox->GetChildrenCount() == 0) Stats_SizeBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	const auto Icon = CreateWidget<UStatIconWidget>(this,IconClass);
	Stats_VerticalBox->AddChild(Icon);
	Icon->AddIcon(NewStat);
	UpdateMargin();
	if(NewStat.MatchesTag(TAG_Stat_Barrier)) AddBarrier(true);
	else if(NewStat.MatchesTag(TAG_Stat_Tough)) AddBarrier(true);
}

void UUnitGameplayWidget::RemoveStat(FGameplayTag StatToRemove)
{
	auto All = Stats_VerticalBox->GetAllChildren();
	const auto Selected = *All.FindByPredicate([&](const UWidget* IconWidget)
	{
		const auto Icon = Cast<UStatIconWidget>(IconWidget);
		return Icon && Icon->Stat == StatToRemove;
	});
	if(Selected) Selected->RemoveFromParent();
	UpdateMargin();
	if(StatToRemove.MatchesTag(TAG_Stat_Barrier)) AddBarrier(false);
	else if(StatToRemove.MatchesTag(TAG_Stat_Tough)) AddTough(false);
}

void UUnitGameplayWidget::AddBarrier(bool Add)
{
	BarrierGlow->SetVisibility(Add ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	BarrierIconBG->SetVisibility(Add ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	BarrierGlow->SetRenderOpacity(0.5f);
	BarrierIconBG->SetRenderOpacity(0.5f);
}

void UUnitGameplayWidget::AddTough(bool Add)
{
	PointsBGTough->SetVisibility(Add ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void UUnitGameplayWidget::LevelUp(int NewLevel)
{
	level = NewLevel;
	UpdateLevel();
}