// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Selectable.h"
#include "ButtonContainer.generated.h"


class UTextBlock;
class UImage;

UCLASS()
class UI_API UButtonContainer : public UUserWidget, public ISelectable 
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void Unselect_Implementation() override;

	virtual  void Select_Implementation() override;

	virtual bool IsSelectedState_Implementation() override;

	virtual USelectEvent* GetSelectEvent_Implementation() override;

	UPROPERTY(EditAnywhere, Category=Default, meta=(MultiLine="true"))
	FText Text;

	UPROPERTY(EditAnywhere, Category=Default)
	UTexture2D* IconTexture;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UImage* Icon;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget,OptionalWidget=true))
	UTextBlock* ButtonName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite)
	USelectEvent* SelectEvent;

	UPROPERTY(BlueprintReadWrite)
	bool IsSelected = false;

	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonClickedEvent OnClicked;

private:

	UFUNCTION(BlueprintCallable)
	void CallOnClicked();
};
