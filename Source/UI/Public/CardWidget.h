// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/RichTextBlock.h"
#include "CardContainer.h"
#include "CardWidget.generated.h"

class UIconsPreset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouse, UUserWidget*, widget);



UCLASS()
class UI_API UCardWidget : public UCardContainer
{
	GENERATED_BODY()

private:
	void SetUnitVisibility(ESlateVisibility VisibilityType) const;
	
public:

	virtual void NativeOnMouseEnter( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeOnMouseLeave( const FPointerEvent& InMouseEvent ) override;
	
	virtual void UpdateCard(UCardPreset* NewCardPreset, int num) override;

	virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UFUNCTION(BlueprintCallable)
	void ActiveOutline(const bool Active);

	UFUNCTION(BlueprintCallable)
	void  PlayHighligh();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Anim_Highlight;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnMouse MouseEnterEvent;

	UPROPERTY(BlueprintAssignable, BlueprintCallable , Category="Button|Event")
	FOnMouse MouseExitEvent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ClassIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* TypeIcon_Description;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PointsBG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* TypeImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* UnitTypeBG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* RarityImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Effect_BG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Effect_Color2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Effect_Color1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Trap_BG;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Trap_Color2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Trap_Color1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LockedImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Outline;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CardNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ManaCost;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Points;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	URichTextBlock* DescriptionText_RichText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* UnitTypeBG_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Effect_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Trap_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* ManaCost_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Type_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* Type_Overlay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* Points_SizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Unit_CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UIconsPreset* Icons;
};
