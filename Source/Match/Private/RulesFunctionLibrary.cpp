#include "RulesFunctionLibrary.h"
#include "AddStatEffect.h"
#include "BoardFunctionLibrary.h"
#include "Card.h"
#include "CardDropTargetInfo.h"
#include "CardSelectTarget.h"
#include "CardSystemFunctionLibrary.h"
#include "CardTarget.h"
#include "MatchGameMode.h"
#include "UnitActor.h"
#include "Kismet/GameplayStatics.h"

int URulesFunctionLibrary::GetWinnerId(TArray<AMatchPlayerState*> GameControllersArray, AMatchGameState* GameState, AMatchGameMode* GameMode)
{
	const int LoserId = UBoardFunctionLibrary::GetPlayerWithoutUnitsInAColumn(GetBoardPlayersData(GameControllersArray),GameState->GetBoard());
	if(LoserId>=0)
	{
		for(int i=0;i < GameControllersArray.Num();i++)
		{
			if(i != LoserId)
			{
				return i;
			}
		}
	}else
	{
		const int MaxGoals = GameMode->MaxGoals;
		for(int i=0;i < GameControllersArray.Num();i++)
		{
			if(GameControllersArray[i]->GetGoals() >= MaxGoals)
			{
				return i;
			}
		}
	}
	return -1;
}

bool URulesFunctionLibrary::TurnEndedByMoves(AMatchGameState* GameState)
{
	const auto PlayerState = GameState->GetCurrentTurnPlayerState();
	return !CanUseAnyCardInHand(PlayerState) 
		&& !UBoardFunctionLibrary::AnySoccerActorCanExecuteMove(GetBoardPlayerData(PlayerState));
}

TArray<FBoardPlayerData> URulesFunctionLibrary::GetBoardPlayersData(const TArray<AMatchPlayerState*>& PlayerStates)
{
	TArray<FBoardPlayerData> Data;
	for (const auto Player : PlayerStates)
	{
		Data.Add(GetBoardPlayerData(Player));
	}
	return Data;
}

FBoardPlayerData URulesFunctionLibrary::GetBoardPlayerData(AMatchPlayerState* PlayerState)
{
	FBoardPlayerData Data;
	Data.PlayerState = PlayerState;
	const auto Controller = PlayerState->GetOwningController();
	Data.Controller = Controller;
	Data.BoardIndex = PlayerState->BoardPlayerId;
	Data.PlayerStatus = PlayerState->PlayerStatus;
	return Data;
}

int URulesFunctionLibrary::GetBetterScore(AMatchGameState* GameState)
{
	auto Players =  GameState->PlayersStateArray;
	int MaxId =-1;
	int MaxScore = 0;
	for(int i=0;i < Players.Num();i++)
	{
		const auto Goals = Players[i]->GetGoals();
		if(Goals > MaxScore)
		{
			MaxScore = Goals;
			MaxId = i;
		}else if(Goals == MaxScore)
		{
			MaxId =-1;
		}
	}
	return MaxId;
}

bool URulesFunctionLibrary::IsPlayerTurn(const AMatchPlayerState* PlayerState)
{
	return GetOnlineGameState(PlayerState->GetWorld())->GetCurrentTurnPlayerState() == PlayerState;
}

TArray<UCard*> URulesFunctionLibrary::ShuffleCards(AMatchPlayerState* Owner, TArray<FCardInDeck> Deck)
{
	TArray<UCard*> DeckHolderCards;
	
	while(Deck.Num() > 0)
	{
		int Id = FMath::RandRange(0,Deck.Num()-1);

		if(Deck[Id].Card == nullptr || Deck[Id].Amount <= 0)
		{
			Deck.RemoveAt(Id);
		}else
		{
			auto Card = NewObject<UCard>(Owner);
			Card->Setup(Deck[Id].Card,Owner);
			DeckHolderCards.Add(Card);
			Deck[Id].Amount--;
			if(Deck[Id].Amount <= 0)
			{
				Deck.RemoveAt(Id);
			}
		}
	}
	return DeckHolderCards;
}

bool URulesFunctionLibrary::CanTryUseCard(UCard* Card, const AMatchPlayerState* PlayerState)
{
	return CanUseCard(Card,PlayerState)
	&& HASONEFLAG(PlayerState->GetMoveState(),ETurnMoveState::WaitMove) == true;
}

bool URulesFunctionLibrary::CanUseCard(UCard* Card, const AMatchPlayerState* PlayerState)
{
	return EnoughMana(Card,PlayerState) && CanUseAnyCard(PlayerState)
	&& FindCardInHand(PlayerState->HandCards,Card) && !IsTrapAndTargetAlreadyHaveTrapCard(Card);
}

bool URulesFunctionLibrary::CanUseAnyCard(const AMatchPlayerState* PlayerState)
{
	return IsPlayerTurn(PlayerState) && HASONEFLAG(PlayerState->GetMoveState(),ETurnMoveState::WaitUseCard) == true;
}

bool URulesFunctionLibrary::CanUseAnyCardInHand(const AMatchPlayerState* PlayerState)
{
	for (const auto Card : PlayerState->HandCards)
	{
		if(CanUseCard(Card,PlayerState)) return true;
	}
	return false;
}

bool URulesFunctionLibrary::IsTrapAndTargetAlreadyHaveTrapCard(UCard* Card)
{
	if(!Card->IsTrap()) return false;
	if(!Card->BoardTargetRequired())
	{
		const auto CartTarget = Card->GetCardTarget(Card->GetOwnerPlayer());
		const auto Targets = CartTarget->GetTargets();
		for (const auto [AbilityContainer, DropTarget] : Targets)
		{
			const auto SoccerActor = Cast<ASoccerActor>(DropTarget);
			if(SoccerActor && !SoccerActor->ContainsTrap())
			{
				return false;
			}
		}
	}else
	{
		const auto CardTarget = Cast<UCardSelectTarget>(Card->GetCardTarget(Card->GetOwnerPlayer()));
		if(!CardTarget) return false;
		const auto Candidates= CardTarget->GetSelectionCandidates();
		for (const auto Candidate : Candidates)
		{
			const auto SoccerActor = Cast<ASoccerActor>(Candidate);
			if(SoccerActor && !SoccerActor->ContainsTrap())
			{
				return false;
			}
		}
	}
	return true;
}

bool URulesFunctionLibrary::IsTrapAndAbilityContainerHaveTrapCard(UCard* Card, const UAbilityContainer* AbilityContainer)
{
	if(!Card->IsTrap()) return false;
	return AbilityContainer->ContainsTrapAbility();
}

bool URulesFunctionLibrary::IsTrapAndSoccerActorHaveTrapCard(UCard* Card, const ASoccerActor* SoccerActor)
{
	if(!Card->IsTrap()) return false;
	return SoccerActor->ContainsTrap();
}

bool URulesFunctionLibrary::EnoughMana(UCard* Card, const AMatchPlayerState* PlayerState)
{
	return IContainsMana::Execute_GetMana(PlayerState) >= GetManaCost(Card);
}

UCard* URulesFunctionLibrary::FindCardInHand(TArray<UCard*> Cards,UCard* CardToFind)
{
	for(const auto Card : Cards)
	{
		if(CardToFind == Card) return Card; 
	}
	return nullptr;
}

int URulesFunctionLibrary::GetManaCost(UCard* Card)
{
	if(const auto TargetUnit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Cast<AMatchPlayerState>(Card->GetOwnerPlayer()))){
		auto NextLevel = UBoardFunctionLibrary::GetUnitNextLevel(TargetUnit) -1;
		NextLevel = FMath::Clamp(NextLevel,0,Card->GetPreset()->CardLevels.Num()-1);
		return Card->GetPreset()->CardLevels[NextLevel].ManaCost;
	}
	return Card->GetPreset()->ManaCost;
}

TArray<UCardAbilityPreset*> URulesFunctionLibrary::GetAbility(const UCard* Card)
{
	if(const auto TargetUnit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Cast<AMatchPlayerState>(Card->GetOwnerPlayer()))){
		return UCardSystemFunctionLibrary::GetAbilityByLevel(Card->GetPreset(),TargetUnit->Level);
	}
	return Card->GetPreset()->AbilityPresets;
}

TArray<FGameplayTag> URulesFunctionLibrary::GetPresetStats(UCardPreset* Preset)
{
	TArray<FGameplayTag> Stats;
	for (auto Ability : Preset->AbilityPresets)
	{
		const auto StatEffect = Cast<UAddStatEffect>(Ability->Effect);
		if(StatEffect) Stats.Add(StatEffect->NewStat);
	}

	for (auto Level : Preset->CardLevels)
	{
		for (auto Ability : Level.AbilityPresets)
		{
			const auto StatEffect = Cast<UAddStatEffect>(Ability->Effect);
			if(StatEffect) Stats.Add(StatEffect->NewStat);
		}
	}
	return Stats;
}

int URulesFunctionLibrary::GetNextLevel(UCard* Card)
{
	if(Card->IsUnit())
	{
		const auto Unit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Cast<AMatchPlayerState>(Card->GetOwnerPlayer()));
		if(!Unit) return 0;
		return UBoardFunctionLibrary::GetUnitNextLevel(Unit);
	}
	return 0;
}

void URulesFunctionLibrary::DropCard(UCard* Card, const TArray<FCardDropTargetInfo>& DropInfos)
{
	if(Card->IsUnit())
	{
		const auto Unit = UBoardFunctionLibrary::GetUnitByPresetAndPlayer(Card->GetPreset(),Cast<AMatchPlayerState>(Card->GetOwnerPlayer()));
		if(!Unit) return;
		const auto AddAbility = !Unit->IsInMaxLevel();
		Unit->LevelUp();
		if(!AddAbility) return;
		FCardDropTargetInfo DropTargetInfo;
		DropTargetInfo.AbilityContainer = Unit->AbilityContainer;
		DropTargetInfo.DropTarget = Unit;
		for (const auto Ability : GetAbility(Card))
		{
			UCardSystemFunctionLibrary::CreateAbility(DropTargetInfo,Ability);
		}
	}else
	{
		for (const auto DropInfo : DropInfos)
		{
			if(!DropInfo.AbilityContainer) return;
			for (const auto Ability : Card->GetPreset()->AbilityPresets)
			{
				UCardSystemFunctionLibrary::CreateAbility(DropInfo,Ability,Card);
			}
		}
	}
}

AMatchPlayerController* URulesFunctionLibrary::GetOnlinePlayerController(UObject* Instigator)
{
	return Cast<AMatchPlayerController>(UGameplayStatics::GetPlayerController(Instigator,0));
}

AMatchGameState* URulesFunctionLibrary::GetOnlineGameState(const UObject* Object)
{
	return Cast<AMatchGameState>(UGameplayStatics::GetGameState(Object));
}

AMatchGameState* URulesFunctionLibrary::GetOnlineGameStateByObject(UObject* Object)
{
	return GetOnlineGameState(Object->GetWorld());
}
