// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "CardBadgeWidget.h"
#include "UserStatusContainer.h"
#include "Data/Public/DeckStructs.h"
#include "UObject/Object.h"
#include "DeckPreviewWidget.generated.h"

class UIconsPreset;

UCLASS()
class UI_API UDeckPreviewWidget : public UUserStatusContainer
{
	GENERATED_BODY()

public:
	virtual void OnUpdateContent_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void UpdateDeck(const FDeck& NewDeck);

	UFUNCTION(BlueprintCallable)
    virtual void PostUpdateDeck();
    
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void OnPostUpdateDeck();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default, meta = (ExposeOnSpawn="true"))
	FDeck DeckData;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor TextColorNormal = FLinearColor::Black;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor TextColorInvalid = FLinearColor::Red;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	UIconsPreset* IconsPreset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<UCardBadgeWidget> BadgeWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<UCardCounterWidget> UnitWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	TSubclassOf<UUserWidget> EmptyWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	int EmptySlotColumnId = 2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	int BadgesPerRow = 3;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* DeckName;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UImage* ClassIcon;
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UImage* GoalkeeperColor;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* TotalCards_Text;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* UnitCardQuantity_Text;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* EffectsQuantity_Text;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* TrapsQuantity_Text;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* UniqueUnitQuantity_Text;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UUniformGridPanel* Badges_Grid;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UVerticalBox* Defenders_VerticalBox;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UVerticalBox* Midfielders_VerticalBox;
	
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UVerticalBox* Attackers_VerticalBox;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCardCounterWidget*> UnitWidgets;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCardBadgeWidget*> BadgeWidgets;
};
