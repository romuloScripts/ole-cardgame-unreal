// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeckPreset.h"
#include "UserStatusStructs.h"
#include "UserStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUserStatusChangedDelegate,const FUserStatus&, NewUserStatus,const FCustomizationData&, NewCustomization);

UCLASS(Blueprintable)
class DATA_API UUserStatusController: public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUserStatus UserStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeckPreset*> Decks;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FUserStatusChangedDelegate OnUserStatusChangedDelegate;

	UFUNCTION(BlueprintCallable)
	void Save(const FUserStatus& NewUserStatus,const FCustomizationData& NewCustomization);

	UFUNCTION(BlueprintCallable)
	bool Load();

	UFUNCTION(BlueprintCallable)
    void SetStatus(FUserStatus& NewUserStatus);
	
	UFUNCTION(BlueprintCallable)
    void SetLevel(int Level);

	UFUNCTION(BlueprintCallable)
    void SetEmblem(UEmblemPreset* Emblem);

	UFUNCTION(BlueprintCallable)
    void SetUniform(UUniformPreset* Uniform);

	UFUNCTION(BlueprintCallable)
    void SetCardBack(UCardBackPreset* CardBack);

	UFUNCTION(BlueprintCallable)
    void SetColorPalette(UColorPreset* ColorPalette);

	UFUNCTION(BlueprintCallable)
	void SetCurrentCustomization(const FName& CurrentCustomization);

	UFUNCTION(BlueprintCallable)
	void AddCustomization(FCustomizationData NewCustomization);

	UFUNCTION(BlueprintCallable)
	void ChangeCustomizationName(const FName& Target,FName NewName);

	UFUNCTION(BlueprintCallable)
	void RemoveCustomization(const FName& CustomizationName);

	UFUNCTION(BlueprintCallable)
	FCustomizationData& GetCurrentCustomization();

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetCustomizationNames();

	UFUNCTION(BlueprintCallable)
	bool CustomizationExist(const FName NewName) const;

	UFUNCTION(BlueprintCallable)
	FName GetNewCustomizationName(FName NewName);

	UFUNCTION(BlueprintCallable)
	void SetCurrentDeck(const FName& CurrentDeck);

	UFUNCTION(BlueprintCallable)
    void AddDeck(FDeck& Deck);

	UFUNCTION(BlueprintCallable)
    TArray<FName> GetDecksNames();

	UFUNCTION(BlueprintCallable)
	FName GetNewDeckName(const FName NewName) const;

	UFUNCTION(BlueprintCallable)
	bool DeckExist(const FName NewName) const;

	UFUNCTION(BlueprintCallable)
	void SetDeckCustomization(FName DeckName, FName CustomizationName);
	
	void CallChangeStatusEvent();

	UFUNCTION(BlueprintCallable)
    void RemoveDeck(const FName& DeckName);

	UFUNCTION(BlueprintCallable)
    FDeck& GetCurrentDeck();
    
	UFUNCTION(BlueprintCallable)
	FCustomizationData& GetCurrentDeckCustomization();

	UFUNCTION(BlueprintCallable)
	FDeck& GetDeckByName(FName DeckName);

	UFUNCTION(BlueprintCallable)
    bool HasCard(UCardPreset* CardPreset);

protected:
	UPROPERTY()
	FDeck EmptyDeck;

	UPROPERTY()
	FCustomizationData EmptyCustomization;
};