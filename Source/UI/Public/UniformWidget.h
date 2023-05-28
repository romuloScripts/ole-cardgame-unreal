// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "UniformContainer.h"
#include "UniformWidget.generated.h"

class UUniformPreset;
/**
 * 
 */
UCLASS()
class UI_API UUniformWidget : public UUniformContainer
{
	GENERATED_BODY()
public:

	//virtual void NativePreConstruct() override;

    virtual void UpdateUniform(UUniformPreset* NewUniform) override;
    
    virtual void UpdateColor(UColorPreset* NewColorPreset) override;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* UniformColor1;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UImage* UniformColor2;
};
