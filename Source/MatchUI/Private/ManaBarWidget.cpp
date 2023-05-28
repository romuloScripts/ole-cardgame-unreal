// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaBarWidget.h"

#include "ManaCellWidget.h"
#include "MatchPlayerController.h"
#include "MatchPlayerState.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"


void UManaBarWidget::UpdateText(int Remain, int Max) const
{
	FString Counter = FString::FromInt(Remain);
	Counter.Append("/");
	Counter.Append(FString::FromInt(Max));
	ManaCountText->SetText(FText::FromString(Counter));
}

bool UManaBarWidget::UpdateManaMax(int Max)
{
	UpdateMana(ManaCurrentCount,ManaMaxCurrentCount);
	if (ManaCellWidget == nullptr || BallPanel == nullptr) return true;

	BallPanel->ClearChildren();
	ManaArray.Empty();
	ManaMax = Max;

	for (int i = 0; i < ManaMax; i++)
	{
		UManaCellWidget* manaInstance = CreateWidget<UManaCellWidget>(this, ManaCellWidget);
		ManaArray.Add(manaInstance);

		UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(BallPanel->AddChild(manaInstance));
		FSlateChildSize size = FSlateChildSize(ESlateSizeRule::Fill);
		size.Value =1;
		slot->SetHorizontalAlignment(HAlign_Fill);
		slot->SetVerticalAlignment(VAlign_Center);
		slot->SetPadding(ManaPadding);
		slot->SetSize(size);
	}
	return false;
}

void UManaBarWidget::SetPlayer(AMatchPlayerState* NewPlayerState,AMatchPlayerController* NewPlayerController)
{
	PlayerState = NewPlayerState;
	if(NewPlayerController && PlayerState->GetPlayerController() == NewPlayerController)
	{
		PlayerController = NewPlayerController;
		PlayerController->OnCanSpendMana.AddDynamic(this,&UManaBarWidget::UpdateCanSpentMana);
	}
	UpdateManaMax(PlayerState->GetMaxMana());
	UpdateColor(NewPlayerState->PlayerStatus.ColorPalette);
}

void UManaBarWidget::NativePreConstruct()
{
	UpdateManaMax(ManaMax);
	Super::NativePreConstruct();
}

void UManaBarWidget::UpdateMana(int Remain, int Max)
{
	Max = FMath::Max(Remain,Max);
	UpdateText(Remain, Max);
	for (int i = 0; i < ManaArray.Num(); i++)
	{
		EManaCellState manaStatus = EManaCellState::Empty;
		if (i < Remain)
		{
			manaStatus = EManaCellState::Full;
		}
		else if (i < Max)
		{
			manaStatus = EManaCellState::Spent;
		}
		ManaArray[i]->UpdateState(manaStatus);
	}
}

void UManaBarWidget::UpdateCanSpentMana(int Value)
{
	if(Value <= 0 || Value > ManaCurrentCount)
	{
		for (int i = 0; i < ManaMaxCurrentCount && i < ManaArray.Num(); i++)
		{
			ManaArray[i]->UpdateState(EManaCellState::ReturnNormalState);
		}
		return;
	}

	for (int i = 0; i < ManaCurrentCount; i++)
	{
		if(i > ManaCurrentCount - Value -1)
		{
			ManaArray[i]->UpdateState(EManaCellState::WillSpend);
		}
	}
}

void UManaBarWidget::UpdateColor(UColorPreset* NewColorPreset)
{
	if(NewColorPreset == nullptr) return;
	
	if (ManaBarBg != nullptr) 
	{
		ManaBarBg->SetColorAndOpacity(NewColorPreset->GetColor(false,UseReserveColor,false));
	}
	Super::UpdateColor(NewColorPreset);
}
