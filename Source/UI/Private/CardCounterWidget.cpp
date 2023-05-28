// Fill out your copyright notice in the Description page of Project Settings.


#include "CardCounterWidget.h"
#include "CardPreset.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UCardCounterWidget::NativeConstruct()
{
	Button->OnHovered.AddDynamic(this,&UCardCounterWidget::Hovered);
	Button->OnUnhovered.AddDynamic(this,&UCardCounterWidget::Unhovered);
	Button->OnClicked.AddDynamic(this,&UCardCounterWidget::Clicked);
}

void UCardCounterWidget::NativeDestruct()
{
	RemoveCardPopUp();
}

void UCardCounterWidget::UpdateAmount_Implementation(int Amount)
{
}

void UCardCounterWidget::Hovered()
{
	if(ShowOutline) OnShowOutline(true);
	GetWorld()->GetTimerManager().SetTimer(TimeHandle,this,&UCardCounterWidget::DisplayCardAtMousePosition,0.5f,false);
}

void UCardCounterWidget::RemoveCardPopUp()
{
	for (auto Card: CardPopUps)
	{
		if(Card)
		{
			Card->RemoveFromParent();
		}
	}
	CardPopUps.Empty();
}

void UCardCounterWidget::Unhovered()
{
	RemoveCardPopUp();
	OnShowOutline(false);
}

void UCardCounterWidget::OnShowOutline_Implementation(bool Show)
{
}

void UCardCounterWidget::Clicked()
{
	RemoveCardPopUp();
	if(CardPreset && OnClickToAdd.IsBound())
	{
		OnClickToAdd.Broadcast(CardPreset);
	}
}

FReply UCardCounterWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && CardPreset && OnClickToRemove.IsBound())
	{
		OnClickToRemove.Broadcast(CardPreset);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCardCounterWidget::DisplayCardAtMousePosition()
{
	if(!IsHovered()) return;
	RemoveCardPopUp();
	const int NumCards = CardPreset->CardLevels.Num()+1;
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	const int OffsetY = -250;
	const int OffsetX = 260;
	const int CenterOffset = (NumCards * OffsetX)/2;

	for (int i=0;i< NumCards;i++)
	{
		auto CardPopUp = CreateWidget<UCardWidget>(this,CardWidget);
		CardPopUp->AddToViewport();
		CardPopUp->UpdateCard(CardPreset,i);
		CardPopUp->UpdateUniform(UniformPreset);
		CardPopUp->UpdateColor(ColorPreset);
		CardPopUp->SetVisibility(ESlateVisibility::HitTestInvisible);
		CardPopUps.Add(CardPopUp);

		const FVector2D Position = NumCards == 1 ?
			FVector2D(MousePosition.X -100.0,MousePosition.Y + OffsetY) :
			FVector2D(MousePosition.X + i * OffsetX -CenterOffset,MousePosition.Y + OffsetY);
		CardPopUp->SetPositionInViewport(Position,true);
	}
}
