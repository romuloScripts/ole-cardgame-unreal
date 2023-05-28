// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeckStructs.h"
#include "UserStatus.h"
#include "UserStatusStructs.h"
#include "DeckFunctionLibrary.generated.h"

static constexpr int GMax_Deck_Cards = 30;
static constexpr int GMax_Unit_Cards = 7;
static constexpr int GMax_Attackers = 3;
static constexpr int GMax_Midfilders = 3;
static constexpr int GMax_Defenders = 3;

class UCardPreset;

UCLASS()
class DATA_API UDeckFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category= Deck)
	static TArray<UCardPreset*> GetUnitsCardsFromDeck(const FDeck& Deck);

	UFUNCTION(BlueprintCallable,Category = Deck)
	static UCardPreset* FindCardInDeck(const FDeck& Deck, const UCardPreset* Card);

	UFUNCTION(BlueprintCallable,Category = Deck)
	static int FindCardIndexInDeck(const FDeck& Deck, const UCardPreset* Card);

	UFUNCTION(BlueprintCallable, Category= Deck)
	static int GetCardAmountInDeck(UCardPreset* card,const FDeck& deck);

	UFUNCTION(BlueprintCallable,Category= Deck)
	static void GetDeckCardsAmount(const FDeck& Deck, FDeckCardsAmount& CardsAmount);

	UFUNCTION(BlueprintCallable,Category= Deck)
	static void IsDeckValid(const FDeckCardsAmount& CardsAmount, UPARAM(meta = (Bitmask, BitmaskEnum = EDeckValidType)) int32& Flags);

	UFUNCTION(BlueprintCallable,Category = Deck)
	static FPlayerStatus CreatePlayerStatus(UUserStatusController* User);

	UFUNCTION(BlueprintCallable,Category = User)
	static FName GetPlayerName(ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable,Category = User)
	static FCustomizationData GetCustomization(const FUserStatus UserStatus);

	UFUNCTION(BlueprintCallable,Category= Deck)
	static EAddCardDeniedType AllowAddCardToDeck(UCardPreset* CardClass,int UsedAmount, int UnlockedAmount, const FDeckCardsAmount& CardsAmount, bool ContainsCard);
};
