// Fill out your copyright notice in the Description page of Project Settings.


#include "CardsShowcaseWidget.h"

#include "CardFilterWidget.h"
#include "SelectionController.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UCardsShowcaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(FilterClassContainer)
	{
		ClassSelectionController = NewObject<USelectionController>();
		ClassSelectionController->InitSelectablePanel(FilterClassContainer);
		for (UObject* Selectable : ClassSelectionController->Selectables)
		{
			UCardFilterWidget* CardFilterWidget = Cast<UCardFilterWidget>(Selectable);
			if(CardFilterWidget)
			{
				CardFilterWidget->OnSendCardClass.AddDynamic(this,&UCardsShowcaseWidget::FilterByClass);
			}
		}
	}

	if(FilterTypeContainer)
	{
		TypeSelectionController = NewObject<USelectionController>();
		TypeSelectionController->InitSelectablePanel(FilterTypeContainer);
		for (UObject* Selectable : TypeSelectionController->Selectables)
		{
			UCardFilterWidget* CardFilterWidget = Cast<UCardFilterWidget>(Selectable);
			if(CardFilterWidget)
			{
				CardFilterWidget->OnSendCardType.AddDynamic(this,&UCardsShowcaseWidget::FilterByType);
			}
		}
	}
	
	if(FilterRarityContainer)
	{
		RaritySelectionController = NewObject<USelectionController>();
		RaritySelectionController->InitSelectablePanel(FilterRarityContainer);
		for (UObject* Selectable : RaritySelectionController->Selectables)
		{
			UCardFilterWidget* CardFilterWidget = Cast<UCardFilterWidget>(Selectable);
			if(CardFilterWidget)
			{
				CardFilterWidget->OnSendCardRarity.AddDynamic(this,&UCardsShowcaseWidget::FilterByRarity);
			}
		}
	}

	if(FilterCostContainer)
	{
		CostSelectionController = NewObject<USelectionController>();
		CostSelectionController->InitSelectablePanel(FilterCostContainer);
		for (UObject* Selectable : CostSelectionController->Selectables)
		{
			UCardFilterWidget* CardFilterWidget = Cast<UCardFilterWidget>(Selectable);
			if(CardFilterWidget)
			{
				CardFilterWidget->OnSendCardCost.AddDynamic(this,&UCardsShowcaseWidget::FilterByCost);
			}
		}
	}
	
	if(ShowAll_Text != nullptr) ShowAllTextNormalColor = ShowAll_Text->GetColorAndOpacity();
	
	if(EditableTextBox_Search)
		EditableTextBox_Search->OnTextCommitted.AddDynamic(this,&UCardsShowcaseWidget::UpdateSearchText);
	if(ShowAll_CheckBox)
		ShowAll_CheckBox->OnCheckStateChanged.AddDynamic(this,&UCardsShowcaseWidget::UpdateShowAll);
	if(Button_Filter_ToggleOff)
		Button_Filter_ToggleOff->OnClicked.AddDynamic(this,&UCardsShowcaseWidget::TopBarShow);
	if(Button_Filter_ToggleOn)
		Button_Filter_ToggleOn->OnClicked.AddDynamic(this,&UCardsShowcaseWidget::TopBarFilterShow);
}

void UCardsShowcaseWidget::UpdateSearchText(const FText& SearchText,ETextCommit::Type Commit)
{
	Search = SearchText;
	OnUpdateContent();
}

void UCardsShowcaseWidget::UpdateShowAll(bool bIsChecked)
{
	ShowAll = bIsChecked;
	if(ShowAll_Text != nullptr)
	{
		ShowAll_Text->SetColorAndOpacity(ShowAll? ShowAllTextSelectedColor : ShowAllTextNormalColor);
	}
	OnUpdateContent();
}

void UCardsShowcaseWidget::TopBarShow()
{
	if(TopBar)
		TopBar->SetVisibility(ESlateVisibility::Visible);
	if(TopBarFilters)
		TopBarFilters->SetVisibility(ESlateVisibility::Hidden);
	if(EditableTextBox_Search)
		EditableTextBox_Search->SetText(FText::GetEmpty());
}

void UCardsShowcaseWidget::TopBarFilterShow()
{
	if(TopBar)
		TopBar->SetVisibility(ESlateVisibility::Hidden);
	if(TopBarFilters)
		TopBarFilters->SetVisibility(ESlateVisibility::Visible);
}

void UCardsShowcaseWidget::FilterByClass(ECardClass CardClass, bool Selected)
{
	if(Selected)
	{
		CardClassFilter = CardClass;
	}else
	{
		CardClassFilter = ECardClass::None;
	}
	OnUpdateContent();
}

void UCardsShowcaseWidget::FilterByType(ECardType CardType, bool Selected)
{
	if(Selected)
	{
		CardTypeFilter = CardType;
	}else
	{
		CardTypeFilter = ECardType::None;
	}
	OnUpdateContent();
}

void UCardsShowcaseWidget::FilterByRarity(ERarityType CardRarity, bool Selected)
{
	if(Selected)
	{
		CardRarityFilter = CardRarity;
	}else
	{
		CardRarityFilter = ERarityType::None;
	}
	OnUpdateContent();
}

void UCardsShowcaseWidget::FilterByCost(int CardCost, bool Selected)
{
	if(Selected)
	{
		FilterCost = true;
		CostFilter = CardCost;
	}else
	{
		FilterCost = false;
	}
	OnUpdateContent();
}
