// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserStatusStructs.h"
#include "Blueprint/UserWidget.h"
#include "UserStatusContainer.generated.h"

class UUserStatusController;
/**
 * 
 */
UCLASS()
class UI_API UUserStatusContainer : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION(BlueprintCallable)
    virtual void UpdateContent();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
    void OnUpdateContent();

protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable)
    void UpdateUserStatus(const FUserStatus& NewUserStatus, const FCustomizationData& NewCustomization);

	UFUNCTION(BlueprintCallable)
    void SetUserStatusController(UUserStatusController* NewUserStatusController);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Default)
	bool UpdatePresetsOnChildren;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FUserStatus UserStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FCustomizationData Customization;
    
	UPROPERTY(BlueprintReadWrite, Category = Default)
	UUserStatusController* UserStatusController;
};
