// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectParams.h"
#include "Selectable.h"

void USelectParams::Init(UObject* ISelectable)
{
	Selectable = ISelectable;
	ISelectable::Execute_GetSelectEvent(Selectable)->OnSelected.AddDynamic(this,&USelectParams::Selected);
}

void USelectParams::Selected()
{
	OnSelectEvent.Broadcast(Selectable);
}