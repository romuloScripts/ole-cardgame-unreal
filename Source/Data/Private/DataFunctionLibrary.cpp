// Fill out your copyright notice in the Description page of Project Settings.


#include "DataFunctionLibrary.h"
#include "CardPreset.h"
#include "ObjectLibrarySubsystem.h"
#include "UserPreset.h"

TArray<UCardPreset*> UDataFunctionLibrary::LoadAllCards()
{
	TArray<UObject*> Search;
	const TSubclassOf<UCardPreset> CardSubclass;

	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/Cards_DataAssets", Search);
	
	TArray<UCardPreset*> SearchDeck;
	
	for (auto Item : Search)
	{
		UCardPreset* CardPreset = Cast<UCardPreset>(Item);
		if (CardPreset)
		{
			SearchDeck.Add(CardPreset);
		}
	}
	
	return SearchDeck;
}

TArray<UUserPreset*> UDataFunctionLibrary::LoadAllUserPresets()
{
	TArray<UObject*> Search;
	const TSubclassOf<UUserPreset> DeckSubclass;

	auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/UserPreset_DataAssets", Search);
	
	TArray<UUserPreset*> SearchUserPreset;
	
	for (const auto Item : Search)
	{
		UUserPreset* UserPreset = Cast<UUserPreset>(Item);
		if (UserPreset)
		{
			SearchUserPreset.Add(UserPreset);
		}
	}
	
	return SearchUserPreset;
}

TArray<UDeckPreset*> UDataFunctionLibrary::LoadAllDecks()
{

	TArray<UObject*> Search;
	const TSubclassOf<UDeckPreset> DeckSubclass;

	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/Decks_DataAssets", Search);
	
	TArray<UDeckPreset*> SearchDeck;
	
	for (auto Item : Search)
	{
		UDeckPreset* DeckPreset = Cast<UDeckPreset>(Item);
		if (DeckPreset)
		{
			SearchDeck.Add(DeckPreset);
		}
	}
	
	return SearchDeck;
}

TArray<UEmblemPreset*> UDataFunctionLibrary::LoadAllEmblems()
{
	TArray<UObject*> Search;
	const TSubclassOf<UEmblemPreset> EmblemSubclass;

	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/Emblems_DataAssets", Search);
	
	TArray<UEmblemPreset*> EmblemPresets;
	
	for (auto Item : Search)
	{
		UEmblemPreset* EmblemPreset = Cast<UEmblemPreset>(Item);
		if (EmblemPreset)
		{
			EmblemPresets.Add(EmblemPreset);
		}
	}
	
	return EmblemPresets;
}

TArray<UUniformPreset*> UDataFunctionLibrary::LoadAllUniforms()
{
	TArray<UObject*> Search;
	const TSubclassOf<UUniformPreset> EmblemSubclass;

	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/Uniforms_DataAssets", Search);
	
	TArray<UUniformPreset*> UniformPresets;
	
	for (auto Item : Search)
	{
		UUniformPreset* EmblemPreset = Cast<UUniformPreset>(Item);
		if (EmblemPreset)
		{
			UniformPresets.Add(EmblemPreset);
		}
	}
	
	return UniformPresets;
}

TArray<UCardBackPreset*> UDataFunctionLibrary::LoadAllCardBacks()
{
	TArray<UObject*> Search;
	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/CardBacks_DataAssets", Search);
	
	TArray<UCardBackPreset*> Presets;
	
	for (const auto Item : Search)
	{
		UCardBackPreset* CardBackPreset = Cast<UCardBackPreset>(Item);
		if (CardBackPreset)
		{
			Presets.Add(CardBackPreset);
		}
	}
	return Presets;
}

TArray<UColorPreset*> UDataFunctionLibrary::LoadAllColorPalettes()
{
	TArray<UObject*> Search;
	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/ColorPalettes_DataAssets", Search);
	
	TArray<UColorPreset*> Presets;
	for (const auto Item : Search)
	{
		UColorPreset* ColorPreset = Cast<UColorPreset>(Item);
		if (ColorPreset)
		{
			Presets.Add(ColorPreset);
		}
	}
	
	return Presets;
}

TArray<UGoalkeepersPreset*> UDataFunctionLibrary::LoadAllGoalkeepers(const ECardClass CardClass)
{
	TArray<UObject*> Search;
	const TSubclassOf<UGoalkeepersPreset> Subclass;

	const auto Library = GEngine->GetEngineSubsystem<UObjectLibrarySubsystem>();
	Library->LoadObjectLibrary("Data/Goalkeepers_DataAssets", Search);
	
	TArray<UGoalkeepersPreset*> Presets;
	
	for (const auto Item : Search)
	{
		UGoalkeepersPreset* GoalkeepersPreset = Cast<UGoalkeepersPreset>(Item);
		if (GoalkeepersPreset)
		{
			if(CardClass== ECardClass::None || CardClass == GoalkeepersPreset->goalkeeperClass)
				Presets.Add(GoalkeepersPreset);
		}
	}
	
	return Presets;
}