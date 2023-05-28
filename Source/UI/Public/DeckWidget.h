// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardContainer.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CardWidget.h"
#include "Data/Public/DeckStructs.h"
#include "Data/Public/GameStateEnums.h"
#include "DeckWidget.generated.h"

class IconsPreset;

UCLASS()
class UI_API UDeckWidget : public UCardContainer
{
	GENERATED_BODY()
	
public:
	
	virtual void NativePreConstruct() override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UFUNCTION(BlueprintCallable)
	void UpdateDeck(const FDeck& NewDeck);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default, meta = (ExposeOnSpawn="true"))
	SelectedMode SelectedMode = SelectedMode::None;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FDeck DeckData;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor ColorNameNormal;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	FLinearColor ColorNameInvalid;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	UIconsPreset* IconsPreset;

	UPROPERTY(BlueprintReadWrite)
	bool Incomplete;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UTextBlock* DeckName;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UImage* ClassIcon;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* deckHolder_Back_color;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* deckHolder_Front_color;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UCardWidget* Card_1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UCardWidget* Card_2;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UCardWidget* Card_3;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UCardWidget* Card_4;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget, OptionalWidget=true))
	UPanelWidget* Alert;
};
