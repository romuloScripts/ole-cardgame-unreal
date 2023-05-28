// Fill out your copyright notice in the Description page of Project Settings.


#include "CardFilterWidget.h"

void UCardFilterWidget::NativeConstruct()
{
	SelectEvent = NewObject<USelectEvent>();
	Button_filter->OnClicked.AddDynamic(this,&UCardFilterWidget::OnClicked);
}

void UCardFilterWidget::Unselect_Implementation()
{
	Selected = false;
	Button_filter->SetBackgroundColor(UnselectedBGColor);
}

void UCardFilterWidget::Select_Implementation()
{
	Selected = true;
	Button_filter->SetBackgroundColor(SelectedBGColor);
	if(SelectEvent->OnSelected.IsBound())
		SelectEvent->OnSelected.Broadcast();
}

bool UCardFilterWidget::IsSelectedState_Implementation()
{
	return Selected;
}

USelectEvent* UCardFilterWidget::GetSelectEvent_Implementation()
{
	return SelectEvent;
}

void UCardFilterWidget::OnClicked()
{
	if(!Selected)
	{
		Execute_Select(this);
	}else
	{
		Execute_Unselect(this);
	}
	OnPosClicked();
}
