// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonContainer.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UButtonContainer::NativePreConstruct()
{
	if(ButtonName != nullptr && !Text.IsEmpty())
	{
		ButtonName->SetText(Text);
	}

	if(Icon != nullptr && IconTexture != nullptr)
	{
		Icon->SetBrushFromTexture(IconTexture);
	}
	Super::NativePreConstruct();
}

void UButtonContainer::NativeConstruct()
{
	SelectEvent = NewObject<USelectEvent>();
	Button->OnClicked.AddDynamic(this,&UButtonContainer::CallOnClicked);
}

void UButtonContainer::CallOnClicked()
{
	Execute_Select(this);
	OnClicked.Broadcast();
}

void UButtonContainer::Unselect_Implementation()
{
	IsSelected = false;
}

void UButtonContainer::Select_Implementation()
{
	IsSelected = true;
	if(SelectEvent->OnSelected.IsBound())
		SelectEvent->OnSelected.Broadcast();
}

bool UButtonContainer::IsSelectedState_Implementation()
{
	return IsSelected;
}

USelectEvent* UButtonContainer::GetSelectEvent_Implementation()
{
	return SelectEvent;
}
