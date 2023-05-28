// Fill out your copyright notice in the Description page of Project Settings.


#include "DropAreaWidget.h"

#include "CardDragDropOperation.h"
#include "HandWidget.h"

bool UDropAreaWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	const auto CardOperation = Cast<UCardDragDropOperation>(InOperation);
	if(!CardOperation) return false;
	HandRef->UseCard(CardOperation->Card);
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDropAreaWidget::SetReferences(UHandWidget* Hand, AMatchPlayerState* Player)
{
	HandRef = Hand;
	PlayerState = Player;
}
