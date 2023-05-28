// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ColorContainer.h"
#include "UObject/Object.h"
#include "EmblemContainer.generated.h"


class EmblemPreset;

UCLASS()
class UI_API UEmblemContainer : public UColorContainer
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateEmblem(UEmblemPreset* NewEmblemPreset);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateEmblem(UEmblemPreset* NewEmblemPreset);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UEmblemPreset* EmblemPreset;
};
