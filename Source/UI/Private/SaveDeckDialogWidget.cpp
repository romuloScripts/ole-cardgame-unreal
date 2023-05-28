// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveDeckDialogWidget.h"

void USaveDeckDialogWidget::NativeConstruct()
{
	if(Button_Save)
		Button_Save->OnClicked.AddDynamic(this,&USaveDeckDialogWidget::RemoveParent);
	if(Button_Cancel)
		Button_Cancel->OnClicked.AddDynamic(this,&USaveDeckDialogWidget::RemoveParent);
	if(Background)
		Background->OnClicked.AddDynamic(this,&USaveDeckDialogWidget::RemoveParent);
	if(Button_Discard)
		Button_Discard->OnClicked.AddDynamic(this,&USaveDeckDialogWidget::RemoveParent);
}

void USaveDeckDialogWidget::RemoveParent()
{
	RemoveFromParent();
}
