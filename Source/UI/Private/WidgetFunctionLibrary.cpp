// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "CardPreset.h"
#include "ButtonContainer.h"
#include "CardBackContainer.h"
#include "CardBadgeWidget.h"
#include "CardContainer.h"
#include "DeckStructs.h"
#include "DeckWidget.h"
#include "EmblemContainer.h"
#include "GoalkeeperContainer.h"
#include "MenuSwitcherParams.h"
#include "UserStatusStructs.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

UCardContainer* UWidgetFunctionLibrary::CreateCardInHorizontalBox(UCardPreset* Card, int Level, TSubclassOf<UCardContainer> WidgetClass, UHorizontalBox* Panel,
                                                                  UUniformPreset* Uniform, UColorPreset* ColorPreset, const bool UseReserveColor, const FMargin Margin)
{
	UCardContainer* CardContainer = CreateWidget<UCardContainer>(Panel,WidgetClass);
	CardContainer->UpdateCard(Card,Level);
	if(Uniform)
		CardContainer->UpdateUniform(Uniform);
	if(ColorPreset)
		CardContainer->UpdateColorAndReserve(ColorPreset,UseReserveColor);
	UHorizontalBoxSlot* Slot = Panel->AddChildToHorizontalBox(CardContainer);
	Slot->SetVerticalAlignment(VAlign_Top);
	Slot->SetHorizontalAlignment(HAlign_Left);
	Slot->SetPadding(Margin);
	auto Size = Slot->GetSize();
	Size.SizeRule = ESlateSizeRule::Automatic;
	Slot->SetSize(Size);
	return CardContainer;
}

void UWidgetFunctionLibrary::CreateCardsInGrid(TArray<UCardPreset*> Cards, TSubclassOf<UCardContainer> WidgetClass,
                                            UUniformGridPanel* Grid, int CardsPerRow, TSubclassOf<UUserWidget> EmptySlot,
                                            UUniformPreset* Uniform, UColorPreset* ColorPreset,
                                            TArray<UCardContainer*>& CardContainers)
{
	CardContainers.Empty();
	Grid->ClearChildren();
	for (UCardPreset* Card : Cards)
	{
		UCardContainer* CardContainer = CreateWidget<UCardContainer>(Grid,WidgetClass);
		CardContainer->UpdateCard(Card,0);
		if(Uniform)
			CardContainer->UpdateUniform(Uniform);
		if(ColorPreset)
			CardContainer->UpdateColor(ColorPreset);
		UUniformGridSlot* Slot = Grid->AddChildToUniformGrid(CardContainer,CardContainers.Num()/CardsPerRow,CardContainers.Num()%CardsPerRow);
		Slot->SetVerticalAlignment(VAlign_Center);
		Slot->SetHorizontalAlignment(HAlign_Center);
		CardContainers.Add(CardContainer);
		if(CardContainers.Num() == 1)
		{
			UUserWidget* Empty = CreateWidget<UUserWidget>(Grid,EmptySlot);
			Grid->AddChildToUniformGrid(Empty,0,CardsPerRow-1);
		}
	}
}

void UWidgetFunctionLibrary::CreateBadgesInGrid(const FDeck& Deck, TSubclassOf<UCardBadgeWidget> WidgetClass,
	UUniformGridPanel* Grid, int BadgesPerRow, TSubclassOf<UUserWidget> EmptySlot, int EmptySlotColumn,
	TArray<UCardBadgeWidget*>& CardBadges)
{
	if(WidgetClass == nullptr) return;
	for (const auto Badge : CardBadges)
	{
		if(Badge) Badge->RemoveFromParent();
	}
	CardBadges.Empty();
	Grid->ClearChildren();
	TArray<UCardPreset*> CardsFilter;
	for (const auto Card : Deck.Cards)
	{
		if(Card.Card == nullptr || !(Card.Card->CardType == ECardType::Effect || Card.Card->CardType == ECardType::Trap)) continue;

		UCardBadgeWidget* CardContainer = CreateWidget<UCardBadgeWidget>(Grid,WidgetClass);
		CardContainer->UpdateCard(Card.Card,0);
		CardContainer->UpdateAmount(Card.Amount);
		UUniformGridSlot* Slot = Grid->AddChildToUniformGrid(CardContainer,CardBadges.Num()/BadgesPerRow,CardBadges.Num()%BadgesPerRow);
		CardBadges.Add(CardContainer);
	}
	if(EmptySlot == nullptr) return;
	UUserWidget* Empty = CreateWidget<UUserWidget>(Grid,EmptySlot);
	UUniformGridSlot* Slot = Grid->AddChildToUniformGrid(Empty,1,EmptySlotColumn);
	Slot->SetVerticalAlignment(VAlign_Fill);
	Slot->SetHorizontalAlignment(HAlign_Fill);
}

void UWidgetFunctionLibrary::CreateTeamFormationInVerticalBox(const FDeck& Deck, TSubclassOf<UCardCounterWidget> WidgetClass,
    TMap<ECardType,UVerticalBox*> VerticalBoxes,TArray<UCardCounterWidget*>& Units)
{
	if(WidgetClass == nullptr) return;
	for (auto Unit : Units)
	{
		if(Unit)
			Unit->RemoveFromParent();
	}
	Units.Empty();

	TMap<ECardType,int> CardCount;
	for (const auto Card : Deck.Cards)
	{
		if(Card.Card == nullptr || !VerticalBoxes.Contains(Card.Card->CardType)) continue;
		UVerticalBox* VerticalBox = VerticalBoxes[Card.Card->CardType];
		if(VerticalBox == nullptr) continue;

		const int MaxCount = VerticalBox->GetChildrenCount();
		const int Index = CardCount.FindOrAdd(Card.Card->CardType,0);

		if(Index < MaxCount)
		{
			UContentWidget* UnitSlot = Cast<UContentWidget>(VerticalBox->GetChildAt(Index));
			if(UnitSlot == nullptr) continue;
			UCardCounterWidget* CardContainer = CreateWidget<UCardCounterWidget>(UnitSlot,WidgetClass);
			CardContainer->UpdateCard(Card.Card,0);
            CardContainer->UpdateAmount(Card.Amount);
			UnitSlot->AddChild(CardContainer);
			CardCount[Card.Card->CardType]++;
			Units.Add(CardContainer);
		}
	}

	for (auto VerticalBox : VerticalBoxes)
	{
		if(VerticalBox.Value == nullptr) continue;
		const int MaxCount = VerticalBox.Value->GetChildrenCount();
		for (int i=0;i<MaxCount; i++)
		{
			if(i>=CardCount.FindOrAdd(VerticalBox.Key,0))
				VerticalBox.Value->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
			else
				VerticalBox.Value->GetChildAt(i)->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

TArray<UCardPreset*> UWidgetFunctionLibrary::FilterCards(TArray<UCardPreset*> Cards, ECardClass CardClassFilter, ECardType CardTypeFilter,
                                                      ERarityType RarityFilter, bool FilterCost, int CardCostFilter, FString Search, bool FilterByCardMap, TMap<UCardPreset*,int> CardMap)
{
	TArray<UCardPreset*> CardsFilter;
	for (UCardPreset* Card : Cards)
	{
		if(CardClassFilter != ECardClass::None && CardClassFilter != Card->CardClass) continue;
		if(CardTypeFilter != ECardType::None && CardTypeFilter != Card->CardType) continue;
		if(RarityFilter != ERarityType::None && RarityFilter != Card->CardRarity) continue;
		if(FilterCost && CardCostFilter != Card->ManaCost) continue;
		if(FilterByCardMap && (!CardMap.Contains(Card) || CardMap[Card] <= 0)) continue;
		
		if(!Search.IsEmpty())
		{
			if(!Card->Name.ToString().Contains(Search) &&
				!Card->CardDescription.ToString().Contains(Search)
			)
			{
				bool bResult = false;
				for(FCard_Level& Card_Level: Card->CardLevels)
				{
					if(Card_Level.CardDescription.ToString().Contains(Search))
					{
						bResult = true;
						continue;
					}	
				}
				if(!bResult) continue;
			}
		}
		CardsFilter.Add(Card);
	}
	return CardsFilter;
}

void UWidgetFunctionLibrary::CreateCardsInGridByNum(int Num, TSubclassOf<UCardContainer> WidgetClass, UUniformGridPanel* Grid,
                                                 int CardsPerRow, TSubclassOf<UUserWidget> EmptySlot,
                                                 TArray<UCardContainer*>& CardContainers)
{
	CardContainers.Empty();
	Grid->ClearChildren();
	for (int i =0; i < Num; i++)
	{
		UCardContainer* CardContainer = CreateWidget<UCardContainer>(Grid,WidgetClass);
		UUniformGridSlot* Slot = Grid->AddChildToUniformGrid(CardContainer,CardContainers.Num()/CardsPerRow,CardContainers.Num()%CardsPerRow);
		Slot->SetVerticalAlignment(VAlign_Center);
		Slot->SetHorizontalAlignment(HAlign_Center);
		CardContainers.Add(CardContainer);
		if(CardContainers.Num() == 1)
		{
			UUserWidget* Empty = CreateWidget<UUserWidget>(Grid,EmptySlot);
			Grid->AddChildToUniformGrid(Empty,0,CardsPerRow-1);
		}
	}
}

void UWidgetFunctionLibrary::CreateElementsInGrid(int num, TSubclassOf<UUserWidget> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow, TArray<UUserWidget*>& Containers)
{
	Containers.Empty();
	Grid->ClearChildren();
	if(num<= 0 || CellsPerRow <= 0) return;
	for (int i = 0; i < num; i++)
	{
		UUserWidget* EmblemContainer = CreateWidget<UUserWidget>(Grid,WidgetClass);
		UUniformGridSlot* Slot = Grid->AddChildToUniformGrid(EmblemContainer,Containers.Num()/CellsPerRow,Containers.Num()%CellsPerRow);
		Slot->SetVerticalAlignment(VAlign_Top);
		Slot->SetHorizontalAlignment(HAlign_Left);
		Containers.Add(EmblemContainer);
	}
}

void UWidgetFunctionLibrary::CreateEmblemsInGrid(TArray<UEmblemPreset*> Emblems, TSubclassOf<UEmblemContainer> WidgetClass,
	UUniformGridPanel* Grid, int CellsPerRow, TArray<UEmblemContainer*>& EmblemsContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Emblems.Num();
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);

	for (int i = 0; i < Num; i++)
	{
		UEmblemContainer* EmblemContainer = Cast<UEmblemContainer>(Containers[i]);
		EmblemContainer->UpdateEmblem(Emblems[i]);
		EmblemsContainers.Add(EmblemContainer);
	}
}

void UWidgetFunctionLibrary::CreateUniformsInGrid(TArray<UUniformPreset*> Emblems,
	TSubclassOf<UUniformContainer> WidgetClass, UUniformGridPanel* Grid, int CellsPerRow,
	TArray<UUniformContainer*>& EmblemsContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Emblems.Num();
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);

	for (int i = 0; i < Num; i++)
	{
		UUniformContainer* EmblemContainer = Cast<UUniformContainer>(Containers[i]);
		EmblemContainer->UpdateUniform(Emblems[i]);
		EmblemsContainers.Add(EmblemContainer);
	}
}

void UWidgetFunctionLibrary::CreateCardBacksInGrid(TArray<UCardBackPreset*> Presets,
	TSubclassOf<UCardBackContainer> WidgetClass, UUniformGridPanel* Grid, int CellsPerRow,
	TArray<UCardBackContainer*>& CardBackContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Presets.Num();
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);

	for (int i = 0; i < Num; i++)
	{
		UCardBackContainer* EmblemContainer = Cast<UCardBackContainer>(Containers[i]);
		EmblemContainer->UpdateCardBack(Presets[i]);
		CardBackContainers.Add(EmblemContainer);
	}
}

void UWidgetFunctionLibrary::CreateColorInGrid(TArray<UColorPreset*> Presets, TSubclassOf<UColorContainer> WidgetClass,
	UUniformGridPanel* Grid, int CellsPerRow, TArray<UColorContainer*>& ColorContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Presets.Num();
	if(Num<= 0 || CellsPerRow <= 0) return;
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);
	
	for (int i = 0; i < Num; i++)
	{
		UColorContainer* ColorContainer = Cast<UColorContainer>(Containers[i]);
		ColorContainer->UpdateColor(Presets[i]);
		ColorContainers.Add(ColorContainer);
	}
}

void UWidgetFunctionLibrary::CreateGoalkeepersInGrid(TArray<UGoalkeepersPreset*> Presets,
	TSubclassOf<UGoalkeeperContainer> WidgetClass, UUniformGridPanel* Grid, int CellsPerRow, UColorPreset* ColorPreset,
	TArray<UGoalkeeperContainer*>& GoalkeeperContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Presets.Num();
	if(Num<= 0 || CellsPerRow <= 0) return;
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);
	
	for (int i = 0; i < Num; i++)
	{
		UGoalkeeperContainer* GoalkeeperContainer = Cast<UGoalkeeperContainer>(Containers[i]);
		GoalkeeperContainer->UpdateGoalkeeper(Presets[i]);
		if(ColorPreset)
			GoalkeeperContainer->UpdateColor(ColorPreset);
		GoalkeeperContainers.Add(GoalkeeperContainer);
	}
}

void UWidgetFunctionLibrary::CreateDecksInGrid(TArray<FDeck> Decks, TSubclassOf<UDeckWidget> WidgetClass,
	UUniformGridPanel* Grid, int CellsPerRow,FUserStatus UserStatus,TArray<UDeckWidget*>& DecksContainers)
{
	TArray<UUserWidget*> Containers;
	const int Num = Decks.Num();
	if(Num<= 0 || CellsPerRow <= 0) return;
	CreateElementsInGrid(Num,WidgetClass,Grid,CellsPerRow,Containers);
	
	for (int i = 0; i < Num; i++)
	{
		UDeckWidget* DeckWidget = Cast<UDeckWidget>(Containers[i]);
		DeckWidget->UpdateDeck(Decks[i]);
		const auto Customizations = UserStatus.Customizations;
		const auto Customization =
			Customizations.Contains(Decks[i].CustomizationName) ?
			Customizations[Decks[i].CustomizationName] :
			Customizations[UserStatus.CurrentCustomization];
		DeckWidget->UpdateUniform(Customization.Uniform);
		DeckWidget->UpdateColor(Customization.ColorPalette);
		DecksContainers.Add(DeckWidget);
	}
}

TArray<UMenuSwitcherParams*> UWidgetFunctionLibrary::BindButtonsWithSwitcher(UPanelWidget* TabsContainer, UWidgetSwitcher* WidgetSwitcher)
{
	TArray<UMenuSwitcherParams*> Params;
	for (const auto Item : TabsContainer->GetAllChildren())
	{
		if(Params.Num() >= WidgetSwitcher->GetNumWidgets()) break;
		
		UButton* Button = Cast<UButton>(Item);

		if(Button == nullptr)
		{
			const UButtonContainer* ButtonContainer = Cast<UButtonContainer>(Item);
			if(ButtonContainer != nullptr)
			{
				Button = ButtonContainer->Button;
			}
		}

		if(Button != nullptr)
		{
			UMenuSwitcherParams* SwitcherParams = CreateSwitcherParams(Params.Num(),WidgetSwitcher,TabsContainer);
			Button->OnClicked.AddDynamic(SwitcherParams,&UMenuSwitcherParams::ChangeMenuTab);
			Params.Add(SwitcherParams);
		}
	}
	return Params;
}

UMenuSwitcherParams* UWidgetFunctionLibrary::CreateSwitcherParams(int index,UWidgetSwitcher* WidgetSwitcher, UObject* owner)
{
	UMenuSwitcherParams* SwitcherParams = NewObject<UMenuSwitcherParams>(owner);
	SwitcherParams->menuIndex = index;
	SwitcherParams->Menu_WidgetSwitcher = WidgetSwitcher;
	return SwitcherParams;
}

void UWidgetFunctionLibrary::UpdateCardBack(UCardBackPreset* CardBack, TArray<UWidget*> Array)
{
	if(CardBack == nullptr) return;
	for(UWidget* InsideWidget: Array)
	{
		if(UCardBackContainer* CardBackContainer = Cast<UCardBackContainer>(InsideWidget))
		{
			CardBackContainer->UpdateCardBack(CardBack);
		}
	}
}

void UWidgetFunctionLibrary::UpdateEmblem(UEmblemPreset* Emblem, TArray<UWidget*> Array)
{
	if(Emblem == nullptr) return;
	for(UWidget* InsideWidget: Array)
	{
		if(UEmblemContainer* EmblemContainer = Cast<UEmblemContainer>(InsideWidget))
		{
			EmblemContainer->UpdateEmblem(Emblem);
		}
	}
}

void UWidgetFunctionLibrary::UpdateUserInWidget(UUserWidget* Widget,const FCustomizationData& Customization)
{
	TArray<UWidget*> WidgetsArray;
	Widget->WidgetTree->GetAllWidgets(WidgetsArray);
	if(Customization.Uniform) UpdateUniformPresetInWidgets(Customization.Uniform,WidgetsArray);
	if(Customization.CardBack) UpdateCardBack(Customization.CardBack,WidgetsArray);
	if(Customization.Emblem) UpdateEmblem(Customization.Emblem,WidgetsArray);
	if(Customization.ColorPalette) UpdateColorPresetInWidgets(Customization.ColorPalette,WidgetsArray);
}

void UWidgetFunctionLibrary::UpdatePresetInWidget(UUserWidget* Widget,UColorPreset* ColorPreset, UUniformPreset* UniformPreset,
                                                  UGoalkeepersPreset* GoalkeepersPreset)
{
	if(ColorPreset == nullptr && UniformPreset == nullptr) return;
	TArray<UWidget*> WidgetsArray;
	Widget->WidgetTree->GetAllWidgets(WidgetsArray);
	if(UniformPreset)
		UpdateUniformPresetInWidgets(UniformPreset,WidgetsArray);
	if(GoalkeepersPreset)
		UpdateGoalkeeperPresetInWidgets(GoalkeepersPreset,WidgetsArray);
	if(ColorPreset)
		UpdateColorPresetInWidgets(ColorPreset,WidgetsArray);
	
}

void UWidgetFunctionLibrary::UpdateColorPresetInWidgets(UColorPreset* ColorPreset, TArray<UWidget*> WidgetsArray)
{
	if(ColorPreset == nullptr) return;
	for(UWidget* InsideWidget: WidgetsArray)
	{
		UColorContainer* ColorContainer = Cast<UColorContainer>(InsideWidget);
		if(ColorContainer)
		{
			ColorContainer->UpdateColor(ColorPreset);
		}
	}
}

void UWidgetFunctionLibrary::UpdateUniformPresetInWidgets(UUniformPreset* UniformPreset, TArray<UWidget*> WidgetsArray)
{
	for(UWidget* InsideWidget: WidgetsArray)
	{
		UUniformContainer* UniformContainer = Cast<UUniformContainer>(InsideWidget);
		if(UniformContainer)
		{
			UniformContainer->UpdateUniform(UniformPreset);
		}
	}
}

void UWidgetFunctionLibrary::UpdateGoalkeeperPresetInWidgets(UGoalkeepersPreset* GoalkeepersPreset, TArray<UWidget*> WidgetsArray)
{
	for(UWidget* InsideWidget: WidgetsArray)
	{
		UGoalkeeperContainer* GoalkeepersContainer = Cast<UGoalkeeperContainer>(InsideWidget);
		if(GoalkeepersContainer)
		{
			GoalkeepersContainer->UpdateGoalkeeper(GoalkeepersPreset);
		}
	}
}

FText UWidgetFunctionLibrary::GetLevelText(int Level)
{
	FString LevelText;
	LevelText.Append("Level");
	LevelText.Append(FString::FromInt(Level));
	return FText::FromString(LevelText);
}




