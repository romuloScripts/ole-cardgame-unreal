// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckFunctionLibrary.h"
#include "CardPreset.h"
#include "CardFunctionLibrary.h"
#include "GameFramework/PlayerState.h"


void UDeckFunctionLibrary::GetDeckCardsAmount(const FDeck& Deck, FDeckCardsAmount& CardsAmount)
{
	for (const auto Card : Deck.Cards)
	{
		if(Card.Card == nullptr) continue;
		CardsAmount.TotalCards += Card.Amount;
		if(UCardFunctionLibrary::IsUnitCard(Card.Card))
		{
			CardsAmount.UniqueUnitCards++;
			CardsAmount.UnitCards+=Card.Amount;
			switch(Card.Card->CardType)
			{
				case ECardType::Attacker: CardsAmount.UniqueAttackers++; break; 
				case ECardType::Midfield: CardsAmount.UniqueMidfielders++; break;
				case ECardType::Defender: CardsAmount.UniqueDefenders++; break; 
			}	
		}else if(Card.Card->CardType == ECardType::Effect)
		{
			CardsAmount.EffectCards+=Card.Amount;
		}else if(Card.Card->CardType == ECardType::Trap)
		{
			CardsAmount.TrapCards+=Card.Amount;
		}
	}
}

void UDeckFunctionLibrary::IsDeckValid(const FDeckCardsAmount& CardsAmount, int32& Flags)
{
	if(CardsAmount.TotalCards != GMax_Deck_Cards)
	{
		SET_BIT(Flags,EDeckValidType::NoTotalCards);
	}
		
	if(CardsAmount.UniqueUnitCards != GMax_Unit_Cards)
		SET_BIT(Flags,EDeckValidType::NoAllUnits);
}

FPlayerStatus UDeckFunctionLibrary::CreatePlayerStatus(UUserStatusController* User)
{
	FPlayerStatus PlayerStatus;
	PlayerStatus.UserName = GetPlayerName(User->GetLocalPlayer<ULocalPlayer>());
	PlayerStatus.Deck = User->GetCurrentDeck();
	PlayerStatus.Level = User->UserStatus.Level;
	const auto Customization = User->GetCurrentDeckCustomization();
	PlayerStatus.Emblem = Customization.Emblem;
	PlayerStatus.Uniform = Customization.Uniform;
	PlayerStatus.CardBack = Customization.CardBack;
	PlayerStatus.ColorPalette = Customization.ColorPalette;
	return PlayerStatus;
}

FName UDeckFunctionLibrary::GetPlayerName(ULocalPlayer* LocalPlayer)
{
	return FName(LocalPlayer->PlayerController->PlayerState->GetPlayerName());
}

FCustomizationData UDeckFunctionLibrary::GetCustomization(const FUserStatus UserStatus)
{
	return UserStatus.Customizations[UserStatus.CurrentCustomization];
}

EAddCardDeniedType UDeckFunctionLibrary::AllowAddCardToDeck(UCardPreset* CardClass, int UsedAmount, int UnlockedAmount, const FDeckCardsAmount& CardsAmount, bool ContainsCard)
{
	if(UsedAmount >= UnlockedAmount) return EAddCardDeniedType::NoCardsInInventory;

	if(CardsAmount.TotalCards >= GMax_Deck_Cards) return EAddCardDeniedType::MaxCards;

	if(ContainsCard || !UCardFunctionLibrary::IsUnitCard(CardClass)) return EAddCardDeniedType::None;

	if(CardsAmount.UniqueUnitCards >= GMax_Unit_Cards) return EAddCardDeniedType::MaxUnitCards;

	switch (CardClass->CardType)
	{
		case ECardType::Attacker:
			if(CardsAmount.UniqueAttackers >= GMax_Attackers) return EAddCardDeniedType::MaxAttackers;
			break;
		case ECardType::Defender:
			if(CardsAmount.UniqueDefenders >= GMax_Defenders) return EAddCardDeniedType::MaxDefenders;
			break;
		case ECardType::Midfield:
			if(CardsAmount.UniqueMidfielders >= GMax_Midfilders) return EAddCardDeniedType::MaxMidfilders;
			break;
	}

	return EAddCardDeniedType::None;
}

TArray<UCardPreset*> UDeckFunctionLibrary::GetUnitsCardsFromDeck(const FDeck& Deck)
{
	TArray<UCardPreset*> CardsDeck;
	for (auto& Elem : Deck.Cards)
	{
		if(Elem.Card != nullptr && UCardFunctionLibrary::IsUnitCard(Elem.Card))
		{
			CardsDeck.Add(Elem.Card);
		}
	}
	
	return CardsDeck;
}

UCardPreset* UDeckFunctionLibrary::FindCardInDeck(const FDeck& Deck, const UCardPreset* Card)
{
	auto FindCard = Deck.Cards.FindByPredicate([&](const FCardInDeck& CardItem)
    {
        return CardItem.Card == Card; 
    });
	if(FindCard == nullptr) return nullptr;
	return FindCard->Card;
}

int UDeckFunctionLibrary::FindCardIndexInDeck(const FDeck& Deck, const UCardPreset* Card)
{
	for (int i =0; i < Deck.Cards.Num();i++)
	{
		if(Deck.Cards[i].Card == Card)
			return i;
	}
	return -1;
}

int UDeckFunctionLibrary::GetCardAmountInDeck(UCardPreset* card,const FDeck& deck)
{
	const auto FindCard = deck.Cards.FindByPredicate([&](const FCardInDeck& CardItem)
    {
        return CardItem.Card == card; 
    });
	if(FindCard == nullptr) return 0;
	return FindCard->Amount;
}