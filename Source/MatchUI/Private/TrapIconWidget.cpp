// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapIconWidget.h"

FReply UTrapIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && OnClickTrapIcon.IsBound() && OnClickTrapIcon.Execute())
	{
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
