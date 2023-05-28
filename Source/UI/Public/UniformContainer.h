// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorContainer.h"

#include "UniformContainer.generated.h"

class UUniformPreset;


UCLASS()
class UI_API UUniformContainer : public UColorContainer
{
	GENERATED_BODY()
public:
	
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
    virtual void UpdateUniform(UUniformPreset* NewUniform);

	UFUNCTION(BlueprintNativeEvent)
    void OnUpdateUniform(UUniformPreset* NewUniform);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUniformPreset* UniformPreset;
};
