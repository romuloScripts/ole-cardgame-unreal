// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/ObjectLibrary.h"
#include "UObject/Object.h"
#include "ObjectLibrarySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DATA_API UObjectLibrarySubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UObjectLibrary* ObjectLibrary;

	UFUNCTION()
	void LoadObjectLibrary(const FString& Path, TArray<UObject*>& Assets);
};
