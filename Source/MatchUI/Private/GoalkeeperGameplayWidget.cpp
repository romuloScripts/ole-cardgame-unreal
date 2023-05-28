#include "GoalkeeperGameplayWidget.h"
#include "GoalkeeperActor.h"
#include "MatchHUDBase.h"
#include "MatchPlayerController.h"
#include "TrapIconWidget.h"


void UGoalkeeperGameplayWidget::Setup_Implementation(ASoccerActor* UnitActor)
{
	Goalkeeper = Cast<AGoalkeeperActor>(UnitActor);
	UseReserveColor = Goalkeeper->UseReserveColor;
	Goalkeeper->OnChangeTrapEffect.AddDynamic(this,&ThisClass::AddTrap);
	if(Goalkeeper->IsLocal())
	{
		TrapIcon->OnClickTrapIcon.BindDynamic(this,&ThisClass::ShowTrapCard);
	}
	Goalkeeper->OnPostTakeDamage.AddDynamic(this,&ThisClass::OnTakeDamage);
	Goalkeeper->OnPostForceDamage.AddDynamic(this,&ThisClass::OnForceTakeDamage);
	Goalkeeper->OnReceivePoints.AddDynamic(this,&ThisClass::OnReceivePoint);
	Goalkeeper->OnUpdatePoints.AddDynamic(this,&ThisClass::SetPoints);
	Goalkeeper->OnFlipVisual.AddDynamic(this,&ThisClass::SetFlip);
	UpdateGoalkeeper(Goalkeeper->GetPreset());
	UpdateColorAndReserve(Goalkeeper->GetColor(),UseReserveColor);
	SetPoints(Goalkeeper->GetPoints());
}

bool UGoalkeeperGameplayWidget::ShowTrapCard()
{
	if(const auto Player = Cast<AMatchPlayerController>(Goalkeeper->GetOwnerPlayerController()); Player && Player->IsLocalPlayerController())
	{
		return Player->GetMatchHud()->ShowCardPreview(Goalkeeper->GetTrapCard(),Player->PlayerStateRef->PlayerStatus);
	}
	return false;
}

void UGoalkeeperGameplayWidget::AddTrap(ETrapAbilityChange AbilityChange)
{
	switch (AbilityChange) {
		case ETrapAbilityChange::Add: TrapIcon->AddTrap(); break;
		case ETrapAbilityChange::Remove: TrapIcon->RemoveTrap(); break;
		case ETrapAbilityChange::Activated: TrapIcon->ActivateTrap(); break;
	}
}

void UGoalkeeperGameplayWidget::SetPoints(int Points)
{
	PointsText->SetText(FText::AsNumber(Points));
}

void UGoalkeeperGameplayWidget::SetFlip(bool Flip)
{
	const auto WidgetTransform = FWidgetTransform(
		FVector2D::ZeroVector,
		FVector2D(Flip?-1:1,1),
		FVector2D::ZeroVector,0);
	GoalkeeperBG->SetRenderTransform(WidgetTransform);
	BPGoalkeeper->SetRenderTransform(WidgetTransform);
}

void UGoalkeeperGameplayWidget::Active(bool Value)
{
	const auto Opacity = FMath::Lerp(DisabledOpacity,1.0f,static_cast<float>(Value));
	SetRenderOpacity(Opacity);
}
