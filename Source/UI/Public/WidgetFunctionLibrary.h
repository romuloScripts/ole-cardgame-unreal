// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetFunctionLibrary.generated.h"

class UCardBadgeWidget;
struct FDeck;
class UVerticalBox;
class UCardCounterWidget;
enum class ECardClass : uint8;
enum class ECardType : uint8;
enum class ERarityType : uint8;
class UEmblemContainer;
class UUniformContainer;
class UCardBackContainer;
class UColorContainer;
class UGoalkeeperContainer;
struct FUserStatus;
class UDeckWidget;
class UMenuSwitcherParams;
class UCardBackPreset;
class UEmblemPreset;
struct FCustomizationData;
class UHorizontalBox;
class UUniformPreset;
class UColorPreset;
class UCardContainer;
class UUniformGridPanel;
class UCardPreset;
class UGoalkeepersPreset;

UCLASS()
class UI_API UWidgetFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = Widget)
	static UCardContainer* CreateCardInHorizontalBox(UCardPreset* Card, int Level, TSubclassOf<UCardContainer> WidgetClass,
	                                          UHorizontalBox* Panel, UUniformPreset* Uniform, UColorPreset* ColorPreset,bool UseReserveColor,
	                                          const FMargin Margin);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=CardContainers))
	static void CreateCardsInGrid(TArray<UCardPreset*> Cards, TSubclassOf<UCardContainer> WidgetClass,
	UUniformGridPanel* Grid, int CardsPerRow, TSubclassOf<UUserWidget> EmptySlot,
	UUniformPreset* Uniform, UColorPreset* ColorPreset,
    TArray<UCardContainer*>& CardContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=CardBadges))
    static void CreateBadgesInGrid(const FDeck& Deck, TSubclassOf<UCardBadgeWidget> WidgetClass,
    UUniformGridPanel* Grid, int BadgesPerRow, TSubclassOf<UUserWidget> EmptySlot, int EmptySlotColumn,
    TArray<UCardBadgeWidget*>& CardBadges);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=Units))
	static void CreateTeamFormationInVerticalBox(const FDeck& Deck, TSubclassOf<UCardCounterWidget> WidgetClass,
    TMap<ECardType,UVerticalBox*> VerticalBoxes,TArray<UCardCounterWidget*>& Units);

	UFUNCTION(BlueprintCallable, Category = Widget)
	static TArray<UCardPreset*> FilterCards(TArray<UCardPreset*> Cards,
    ECardClass CardClassFilter, ECardType CardTypeFilter,ERarityType RarityFilter,
    bool FilterCost, int CardCostFilter, FString Search, bool FilterByCardMap, TMap<UCardPreset*,int> CardMap);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=CardContainers))
    static void CreateCardsInGridByNum(int Num, TSubclassOf<UCardContainer> WidgetClass,
    UUniformGridPanel* Grid, int CardsPerRow, TSubclassOf<UUserWidget> EmptySlot,
    TArray<UCardContainer*>& CardContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=Containers))
	static void CreateElementsInGrid(int num, TSubclassOf<UUserWidget> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow, TArray<UUserWidget*>& Containers);
	
	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=EmblemsContainers))
    static void CreateEmblemsInGrid(TArray<UEmblemPreset*> Emblems, TSubclassOf<UEmblemContainer> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow,TArray<UEmblemContainer*>& EmblemsContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=EmblemsContainers))
    static void CreateUniformsInGrid(TArray<UUniformPreset*> Emblems, TSubclassOf<UUniformContainer> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow,TArray<UUniformContainer*>& EmblemsContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=CardBackContainers))
    static void CreateCardBacksInGrid(TArray<UCardBackPreset*> Presets, TSubclassOf<UCardBackContainer> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow,TArray<UCardBackContainer*>& CardBackContainers);
	
	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=ColorContainers))
    static void CreateColorInGrid(TArray<UColorPreset*> Presets, TSubclassOf<UColorContainer> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow,TArray<UColorContainer*>& ColorContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=GoalkeeperContainers))
    static void CreateGoalkeepersInGrid(TArray<UGoalkeepersPreset*> Presets, TSubclassOf<UGoalkeeperContainer> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow, UColorPreset* ColorPreset,TArray<UGoalkeeperContainer*>& GoalkeeperContainers);

	UFUNCTION(BlueprintCallable, Category = Widget, meta = (DeterminesOutputType = WidgetClass, DynamicOutputParam=DecksContainers))
    static void CreateDecksInGrid(TArray<FDeck> Decks, TSubclassOf<UDeckWidget> WidgetClass,
    UUniformGridPanel* Grid, int CellsPerRow,FUserStatus UserStatus, TArray<UDeckWidget*>& DecksContainers);

	UFUNCTION(BlueprintCallable,Category= Widget)
	static TArray<UMenuSwitcherParams*> BindButtonsWithSwitcher(UPanelWidget* TabsContainer, UWidgetSwitcher* WidgetSwitcher);

	UFUNCTION(BlueprintCallable,Category= Widget)
	static UMenuSwitcherParams* CreateSwitcherParams(int index, UWidgetSwitcher* WidgetSwitcher, UObject* owner);

	UFUNCTION(BlueprintCallable,Category=Widget)
	static void UpdateCardBack(UCardBackPreset* CardBack, TArray<UWidget*> Array);

	UFUNCTION(BlueprintCallable,Category=Widget)
	static void UpdateEmblem(UEmblemPreset* Emblem, TArray<UWidget*> Array);
	
	UFUNCTION(BlueprintCallable,Category=Widget)
	static void UpdateUserInWidget(UUserWidget* Widget,const FCustomizationData& Customization);
	
	UFUNCTION(BlueprintCallable,Category=Widget)
	static void UpdatePresetInWidget(UUserWidget* Widget,UColorPreset* ColorPreset, UUniformPreset* UniformPreset, UGoalkeepersPreset* GoalkeepersPreset = nullptr);

	UFUNCTION(BlueprintCallable,Category=Widget)
    static void UpdateColorPresetInWidgets(UColorPreset* ColorPreset, TArray<UWidget*> WidgetsArray);

	UFUNCTION(BlueprintCallable,Category=Widget)
    static void UpdateUniformPresetInWidgets(UUniformPreset* UniformPreset, TArray<UWidget*> WidgetsArray);

	UFUNCTION(BlueprintCallable,Category=Widget)
    static void UpdateGoalkeeperPresetInWidgets(UGoalkeepersPreset* GoalkeepersPreset, TArray<UWidget*> WidgetsArray);
	
	UFUNCTION(BlueprintCallable,Category = User)
	static FText GetLevelText(int Level);
};
