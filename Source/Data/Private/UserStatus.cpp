
#include "UserStatus.h"
#include "OleSaveGame.h"
#include "DataFunctionLibrary.h"
#include "UserPreset.h"
#include "Kismet/GameplayStatics.h"

void UUserStatusController::Initialize(FSubsystemCollectionBase& Collection)
{
    auto UserPreset = UDataFunctionLibrary::LoadAllUserPresets();
	if(UserPreset.Num()>0)
	{
		UserStatus = UserPreset[0]->UserStatus;
		Decks = UserPreset[0]->Decks;
	}
	const auto Loaded = Load();
	if(UserPreset.Num()>0 && UserStatus.CurrentCustomization.IsNone())
	{
		const auto Default = UserPreset[0]->DefaultCustomization->DefaultCustomization;
		UserStatus.Customizations.Add(Default.CustomizationName,Default);
		UserStatus.CurrentCustomization = Default.CustomizationName;
	}
	for(UCardPreset* Card: UDataFunctionLibrary::LoadAllCards())
	{
		if(Card->StartUnlockedInGame>0)
		{
			if(!UserStatus.Cards.Contains(Card) || Card->StartUnlockedInGame > UserStatus.Cards[Card]){
				UserStatus.Cards.Add(Card,Card->StartUnlockedInGame);
			}
		}
	}

	if(!Loaded)
	{
		for(const UDeckPreset* DeckPreset: Decks)
		{
			if(!DeckPreset || UserStatus.Decks.Contains(DeckPreset->Deck.DeckName)) continue;
			UserStatus.Decks.Add(DeckPreset->Deck.DeckName,DeckPreset->Deck);
		}
	}
	OnUserStatusChangedDelegate.AddDynamic(this,&UUserStatusController::Save);
}

void UUserStatusController::Save(const FUserStatus& NewUserStatus,const FCustomizationData& NewCustomization)
{
	if (UOleSaveGame* SaveGameInstance = Cast<UOleSaveGame>(UGameplayStatics::CreateSaveGameObject(UOleSaveGame::StaticClass())))
	{
		SaveGameInstance->UserStatus = UserStatus;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "OleSav", 0);
	}
}

bool UUserStatusController::Load()
{
	if (UOleSaveGame* LoadedGame = Cast<UOleSaveGame>(UGameplayStatics::LoadGameFromSlot("OleSav", 0)))
	{
		UserStatus = LoadedGame->UserStatus;
		return true;
	}
	return false;
}

void UUserStatusController::SetStatus(FUserStatus& NewUserStatus)
{
	UserStatus = NewUserStatus;
	CallChangeStatusEvent();
}

void UUserStatusController::SetLevel(int Level)
{
	UserStatus.Level = Level;
	CallChangeStatusEvent();
}

void UUserStatusController::SetEmblem(UEmblemPreset* Emblem)
{
	const auto Current = UserStatus.CurrentCustomization;
	if(Emblem == UserStatus.Customizations[Current].Emblem) return;
	UserStatus.Customizations[Current].Emblem = Emblem;
	CallChangeStatusEvent();
}

void UUserStatusController::SetUniform(UUniformPreset* Uniform)
{
	const auto Current = UserStatus.CurrentCustomization;
	if(Uniform == UserStatus.Customizations[Current].Uniform) return;
	UserStatus.Customizations[Current].Uniform = Uniform;
	CallChangeStatusEvent();
}

void UUserStatusController::SetCardBack(UCardBackPreset* CardBack)
{
	const auto Current = UserStatus.CurrentCustomization;
	if(CardBack == UserStatus.Customizations[Current].CardBack) return;
	UserStatus.Customizations[Current].CardBack = CardBack;
	CallChangeStatusEvent();
}

void UUserStatusController::SetColorPalette(UColorPreset* ColorPalette)
{
	const auto Current = UserStatus.CurrentCustomization;
	if(ColorPalette == UserStatus.Customizations[Current].ColorPalette) return;
	UserStatus.Customizations[Current].ColorPalette = ColorPalette;
	CallChangeStatusEvent();
}

void UUserStatusController::SetCurrentCustomization(const FName& CurrentCustomization)
{
	if(CurrentCustomization == UserStatus.CurrentCustomization) return;
	UserStatus.CurrentCustomization = CurrentCustomization;
	CallChangeStatusEvent();
}

void UUserStatusController::AddCustomization(FCustomizationData NewCustomization)
{
	const auto Name = GetNewCustomizationName(NewCustomization.CustomizationName);
	NewCustomization.CustomizationName = Name;
	UserStatus.Customizations.Add(Name,NewCustomization);
	SetCurrentCustomization(Name);
	CallChangeStatusEvent();
}

void UUserStatusController::ChangeCustomizationName(const FName& Target,FName NewName)
{
	if(!UserStatus.Customizations.Contains(Target)) return;
	if(Target == NewName) return;
	NewName = GetNewCustomizationName(NewName);
	auto Customization = UserStatus.Customizations[Target];
	UserStatus.Customizations.Remove(Target);
	Customization.CustomizationName = NewName;
	UserStatus.Customizations.Add(NewName,Customization);
	for (auto Deck : UserStatus.Decks)
	{
		if(Deck.Value.CustomizationName == Target)
		{
			auto NewDeck = Deck.Value;
			NewDeck.CustomizationName = NewName;
			UserStatus.Decks[NewDeck.DeckName] = NewDeck;
		} 
	}
	SetCurrentCustomization(NewName);
	CallChangeStatusEvent();
}

void UUserStatusController::RemoveCustomization(const FName& CustomizationName)
{
	if(UserStatus.Customizations.Num() <= 1) return;
	if(!UserStatus.Customizations.Contains(CustomizationName)) return;

	if(UserStatus.CurrentCustomization == CustomizationName)
	{
		TArray<FCustomizationData> CustomizationArray;
		UserStatus.Customizations.GenerateValueArray(CustomizationArray);
		const auto Index = CustomizationArray.IndexOfByPredicate([&] (FCustomizationData Customization)
		{
			return CustomizationName == Customization.CustomizationName;
		});
		SetCurrentCustomization(CustomizationArray[Index <= 0 ? 1 : Index-1].CustomizationName);
	}
	UserStatus.Customizations.Remove(CustomizationName);
	CallChangeStatusEvent();
}

FCustomizationData& UUserStatusController::GetCurrentCustomization()
{
	if(UserStatus.Customizations.Contains(UserStatus.CurrentCustomization))
		return UserStatus.Customizations[UserStatus.CurrentCustomization];
	TArray<FCustomizationData> CustomizationArray;
	UserStatus.Customizations.GenerateValueArray(CustomizationArray);
	if(CustomizationArray.Num() > 0)
		return CustomizationArray[0];
	return EmptyCustomization;
}

TArray<FName> UUserStatusController::GetCustomizationNames()
{
	TArray<FName> Names;
	UserStatus.Customizations.GetKeys(Names);
	return Names;
}

bool UUserStatusController::CustomizationExist(const FName NewName) const
{
	return UserStatus.Customizations.Contains(NewName);
}

FName UUserStatusController::GetNewCustomizationName(FName NewName)
{
	if(NewName.IsNone()) NewName = FName("Default");
	int Num=1;
	FString NameString = NewName.ToString();
	while (UserStatus.Customizations.Contains(FName(NameString)))
	{
		NameString = NewName.ToString().Append(FString::FromInt(Num));
		Num++;
	}
	return FName(NameString);
}

void UUserStatusController::SetCurrentDeck(const FName& CurrentDeck)
{
	UserStatus.CurrentDeck = CurrentDeck;
	CallChangeStatusEvent();
}

void UUserStatusController::AddDeck(FDeck& Deck)
{
	if(UserStatus.Decks.Contains(Deck.DeckName))
	{
		UserStatus.Decks[Deck.DeckName] = Deck;
	}else
	{
		UserStatus.Decks.Add(Deck.DeckName,Deck);
	}
	
	if(UserStatus.Decks.Num() == 1)
	{
		SetCurrentDeck(Deck.DeckName);
	}
	CallChangeStatusEvent();
}

TArray<FName> UUserStatusController::GetDecksNames()
{
	TArray<FName> Names;
	UserStatus.Decks.GetKeys(Names);
	return Names;
}

FName UUserStatusController::GetNewDeckName(const FName NewName) const
{
	int Num=1;
	FString NameString = NewName.ToString();
	while (UserStatus.Decks.Contains(FName(NameString)))
	{
		NameString = NewName.ToString().Append(FString::FromInt(Num));
		Num++;
	}
	return FName(NameString);
}

bool UUserStatusController::DeckExist(const FName NewName) const
{
	return UserStatus.Decks.Contains(NewName);
}

void UUserStatusController::SetDeckCustomization(FName DeckName, FName CustomizationName)
{
	if(!UserStatus.Decks.Contains(DeckName) || UserStatus.Decks[DeckName].CustomizationName == CustomizationName) return;
	UserStatus.Decks[DeckName].CustomizationName = CustomizationName;
	CallChangeStatusEvent();
}

void UUserStatusController::CallChangeStatusEvent()
{
	OnUserStatusChangedDelegate.Broadcast(UserStatus,GetCurrentCustomization());
}

void UUserStatusController::RemoveDeck(const FName& DeckName)
{
	if(!UserStatus.Decks.Contains(DeckName)) return;
	UserStatus.Decks.Remove(DeckName);
	if(UserStatus.Decks.Num() <= 0)
	{
		SetCurrentDeck(FName());
	}
	CallChangeStatusEvent();
}

FDeck& UUserStatusController::GetCurrentDeck()
{
	if(UserStatus.Decks.Contains(UserStatus.CurrentDeck)) return UserStatus.Decks[UserStatus.CurrentDeck];
	TArray<FDeck> DeckArray;
	UserStatus.Decks.GenerateValueArray(DeckArray);
	if(DeckArray.Num() > 0) return DeckArray[0];
	return EmptyDeck;
}

FCustomizationData& UUserStatusController::GetCurrentDeckCustomization()
{
	const auto Deck = GetCurrentDeck();
	return UserStatus.Customizations.Contains(Deck.CustomizationName) ?
		UserStatus.Customizations[Deck.CustomizationName] :
		GetCurrentCustomization();
}

FDeck& UUserStatusController::GetDeckByName(FName DeckName)
{
	if(!UserStatus.Decks.Contains(DeckName)) return EmptyDeck;
	return UserStatus.Decks[DeckName];
}

bool UUserStatusController::HasCard(UCardPreset* CardPreset)
{
	return UserStatus.Cards.Contains(CardPreset) && UserStatus.Cards[CardPreset] > 0;
}
