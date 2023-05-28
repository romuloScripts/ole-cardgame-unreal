// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardFunctionLibrary.h"
#include "CardFunctionLibrary.h"
#include "DeckFunctionLibrary.h"
#include "Board.h"
#include "BoardSlot.h"
#include "GoalkeeperActor.h"
#include "StatComponent.h"
#include "GameTags.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

bool UBoardFunctionLibrary::HaveOpponentsInFront(const bool Aerial,ABoardSlot* CurrentSlot, ASoccerActor* TargetActor,int TargetSlotGridX, int HorizontalDirection, int PlayerId)
{
	const auto Next = HorizontalDirection >= 1 ? CurrentSlot->RightSlot : CurrentSlot->LeftSlot;
	if(CurrentSlot->AttachedUnit == TargetActor || Next == nullptr || Next->AttachedUnit == TargetActor
		|| (Aerial && Next->GridId.X > TargetSlotGridX))
	{
		return false;
	}
	if(Next->PlayerId != PlayerId)
	{
		if(!Aerial && Next->AttachedUnit && Next->AttachedUnit->IsActivated()) return true;
		if(Aerial)
		{
			const auto Column = GetSlotsByColumn(GetBoard(Next),Next->GridId.X);
			for (const auto Slot : Column)
			{
				const auto Unit = Slot->AttachedUnit;
				const auto StatComponent = GetStatComponent(Unit);
				const bool ContainsStat = StatComponent && StatComponent->ContainsStat(TAG_Stat_Barrier);
				if(
					Unit && ContainsStat
					&& Unit->IsActivated()
					&& FMath::Abs(Slot->GridId.Y - Next->GridId.Y) <= 1)
				{
					return true;
				}
			}
		}
	}
	return HaveOpponentsInFront(Aerial,Next,TargetActor,TargetSlotGridX,HorizontalDirection,PlayerId);
}

bool UBoardFunctionLibrary::IsPassAllowed(ABoardSlot* TargetSlot,int MaxHorizontalDistance, bool& OpponentsInFront)
{
	OpponentsInFront = false;
	const auto TargetUnit = TargetSlot->AttachedUnit;
	if(TargetUnit == nullptr) return false;
	const auto BallUnit = Cast<AUnitActor>(GetBall(TargetSlot->GetWorld())->AttachedActor);
	if(BallUnit == nullptr) return false;
	const auto BallSlot = BallUnit->CurrentSlot;
	const FIntPoint SlotPos = TargetSlot->GridId;
	const FIntPoint BallPos = BallSlot->GridId;
	const auto StatComponent = GetStatComponent(BallUnit);
	const bool Aerial = StatComponent && StatComponent->ContainsStat(TAG_Stat_Aerial);
	const FIntPoint MaxDistance(MaxHorizontalDistance,Aerial ? 1 : 0);
	const FIntPoint Distance(FMath::Abs(SlotPos.X - BallPos.X),FMath::Abs(SlotPos.Y - BallPos.Y));
	bool Allowed = Distance.X == 0 || (Distance.X <= MaxDistance.X && Distance.Y <= MaxDistance.Y);
	if(Allowed && Distance.X != 0)
	{
		OpponentsInFront = HaveOpponentsInFront(Aerial,BallSlot,TargetUnit,SlotPos.X,SlotPos.X - BallPos.X,BallSlot->PlayerId);
		Allowed = !OpponentsInFront;
	}
	return Allowed;
}

bool UBoardFunctionLibrary::IsKickAllowed(AGoalkeeperActor* GoalkeeperActor,int MaxHorizontalDistance,bool& OpponentsInFront)
{
	OpponentsInFront = false;
	if(GoalkeeperActor == nullptr) return false;
	const auto Ball = GetBall(GoalkeeperActor);
	if(Ball == nullptr) return false;
	const auto BallUnit = Cast<AUnitActor>(Ball->AttachedActor);
	if(!BallUnit) return false;
	const auto BallSlot = BallUnit->CurrentSlot;
	if(!BallSlot || GoalkeeperActor->GetPlayerId() == BallUnit->GetPlayerId()) return false;
	const bool Right = GoalkeeperActor->GetPlayerId() == 1;
	const auto TargetSlot = GoalkeeperActor->GetCloserSlot(BallSlot->GridId);
	const FIntPoint SlotPos = TargetSlot->GridId;
	const FIntPoint BallPos = BallSlot->GridId;
	const auto StatComponent = GetStatComponent(BallUnit);
	const bool Aerial = StatComponent && StatComponent->ContainsStat(TAG_Stat_Aerial);
	const FIntPoint MaxDistance(MaxHorizontalDistance,Aerial ? 1 : 0);
	const FIntPoint Distance(FMath::Abs(SlotPos.X - BallPos.X),FMath::Abs(SlotPos.Y - BallPos.Y));
	bool Allowed = (Distance.X <= MaxDistance.X && Distance.Y <= MaxDistance.Y);
	
	if(Allowed)
	{
		OpponentsInFront = HaveOpponentsInFront(Aerial,BallSlot,GoalkeeperActor,SlotPos.X,Right ? 1 : -1,BallSlot->PlayerId);
		Allowed = !OpponentsInFront;
	}
	return Allowed;
}

bool UBoardFunctionLibrary::HaveUnitsInAllColumns(int PlayerId, ABoard* Board)
{
	for (int X=0; X< Board->Columns.Num(); X++)
	{
		if(Board->Columns[X].PlayerId != PlayerId) continue;
		bool ColumnIsEmpty=true;
		for (int Y=0; Y < Board->Lines; Y++)
		{
			const auto Slot = Board->GetSlotAtPoint(FIntPoint(X,Y));
			if(Slot->AttachedUnit && !Slot->AttachedUnit->GetRedCard())
			{
				ColumnIsEmpty = false;
				break;
			}
		}
		if(ColumnIsEmpty) return false;
	}
	return true;
}

int UBoardFunctionLibrary::GetPlayerWithoutUnitsInAColumn(const TArray<FBoardPlayerData>& GameControllersArray, ABoard* Board)
{
	for(int i=0;i <= GameControllersArray.Num();i++)
	{
		if(!HaveUnitsInAllColumns(i,Board))
		{
			return i;
		}
	}
	return -1;
}

TArray<ABoardSlot*> UBoardFunctionLibrary::GetMiddleColumnSlotsByPlayer(int PlayerId, ABoard* Board)
{
	TArray<ABoardSlot*> Slots;
	int Middle = Board->Columns.Num()/2 -1;
	int Sign = PlayerId >= 1 ? 1 : -1;
	for (int X = Middle; X >= 0 && X < Board->Columns.Num(); X += Sign)
	{
		if(Board->Columns[X].PlayerId == PlayerId)
		{
			for (int Y = 0; Y < Board->Lines; Y++)
			{
				Slots.Add(Board->GetSlotAtPoint(FIntPoint(X,Y)));
			}
			break;
		}
	}
	return  Slots;
}

TArray<ABoardSlot*> UBoardFunctionLibrary::GetSlotsByPlayer(int PlayerId, ABoard* Board)
{
	TArray<ABoardSlot*> Slots;
	for (int X=0; X< Board->Columns.Num(); X++)
	{
		if(Board->Columns[X].PlayerId != PlayerId) continue;
		for (int Y=0; Y < Board->Lines; Y++)
		{
			Slots.Add(Board->GetSlotAtPoint(FIntPoint(X,Y)));
		}
	}
	return Slots;
}

TArray<ABoardSlot*> UBoardFunctionLibrary::GetSlotsByColumn(ABoard* Board, const int Column)
{
	TArray<ABoardSlot*> Slots;
	for (int Y=0; Y < Board->Lines; Y++)
	{
		Slots.Add(Board->GetSlotAtPoint(FIntPoint(Column,Y)));
	}
	return Slots;
}

TArray<AUnitActor*> UBoardFunctionLibrary::GetUnitsByType(TArray<AUnitActor*> UnitArray,const ECardType& CardType)
{
	TArray<AUnitActor*> Units;
	for (auto Unit : UnitArray)
	{
		if(Unit->CardPreset->CardType == CardType)
		{
			Units.Add(Unit);
		}
	}
	return Units;
}

AUnitActor* UBoardFunctionLibrary::GetUnitByPresetAndPlayer(UCardPreset* Preset, APlayerState* PlayerState)
{
	if(!PlayerState || !UCardFunctionLibrary::IsUnitCard(Preset)) return nullptr;
	const auto Board = GetBoard(PlayerState->GetWorld());
	if(!Board) return nullptr;
	const auto Units = Board->GetAllUnits();
	for (const auto Unit : Units)
	{
		if(Unit->GetOwnerPlayerState() == PlayerState && Preset == Unit->CardPreset)
		{
			return Unit;
		}
	}
	return nullptr;
}

int UBoardFunctionLibrary::GetUnitNextLevelByPreset(UCardPreset* Preset, APlayerState* PlayerState)
{
	const auto Unit = GetUnitByPresetAndPlayer(Preset,PlayerState);
	return GetUnitNextLevel(Unit);
}

int UBoardFunctionLibrary::GetUnitNextLevel(AUnitActor* Unit)
{
	return Unit ? Unit->Level + 1 : 0;
}

ABoardSlot* UBoardFunctionLibrary::GetSlotByActor(ASoccerActor* Actor)
{
	const auto Board = GetBoard(Actor);
	for (const auto Slot : Board->SlotMap)
	{
		if(Slot->AttachedUnit == Actor) return Slot;
	}
	return nullptr;
}

bool UBoardFunctionLibrary::GetPlayersUseSameColor(const TArray<FPlayerStatus>& Players)
{
	FGameplayTagContainer ColorTags;
	for(int i = 0; i < Players.Num();i++)
	{
		const auto Color = Players[i].ColorPalette->ColorTag;
		if(ColorTags.HasAny(Color))
		{
			return true;
		}
		ColorTags.AppendTags(Color);
	}
	return false;
}

bool UBoardFunctionLibrary::BallInPossesOfOpponentGoalkeeper(ABoard* Board, int PlayerId)
{
	const auto Goalkeeper= Cast<AGoalkeeperActor>(Board->BallActor->AttachedActor);
	if(!Goalkeeper) return false;
	return Goalkeeper->GetPlayerId() != PlayerId;
}

bool UBoardFunctionLibrary::BallInPossesOfGoalkeeper(ABoard* Board, int PlayerId)
{
	const auto Goalkeeper= Cast<AGoalkeeperActor>(Board->BallActor->AttachedActor);
	if(!Goalkeeper) return false;
	return Goalkeeper->GetPlayerId() == PlayerId;
}

bool UBoardFunctionLibrary::BallInPossesOfActor(ASoccerActor* SoccerActor)
{
	if(SoccerActor == nullptr) return false;
	const auto Board = GetBoard(SoccerActor->GetWorld());
	return Board->BallActor->AttachedActor == SoccerActor;
}

ABallActor* UBoardFunctionLibrary::GetBall(const UObject* Object)
{
	return GetBoard(Object)->BallActor;
}

TArray<AUnitActor*> UBoardFunctionLibrary::GetAllUnits(const UObject* WorldContextObject)
{
	return GetBoard(WorldContextObject->GetWorld())->GetAllUnits();
}

TArray<AUnitActor*> UBoardFunctionLibrary::GetAllUnitsOfPlayer(const FBoardPlayerData& PlayerState)
{
	const auto AllUnits = GetAllUnits(PlayerState.PlayerState);
	TArray<AUnitActor*> PlayerUnits;
	for (auto Unit : AllUnits)
	{
		if(Unit->GetPlayerId() == PlayerState.BoardIndex)
		{
			PlayerUnits.Add(Unit);
		}
	}
	return PlayerUnits;
}

bool UBoardFunctionLibrary::AnySoccerActorCanExecuteMove(const FBoardPlayerData& PlayerState)
{
	for (const auto Unit : GetAllUnitsOfPlayer(PlayerState))
	{
		if(Unit && Unit->CanExecuteAnyMove()) return true;
	}
	const auto Goalkeeper = GetGoalkeeperActor(PlayerState,false);
	return Goalkeeper->CanExecuteAnyMove();
}

void UBoardFunctionLibrary::GetOpponentPlayer(APlayerState* PlayerState, TSubclassOf<APlayerState> PlayerStateClass, APlayerState*& OpponentPlayerState)
{
	for(int i = 0; i < UGameplayStatics::GetNumPlayerStates(PlayerState); i++)
	{
		const auto Candidate = UGameplayStatics::GetPlayerState(PlayerState,i);
		if(Candidate != PlayerState)
		{
			OpponentPlayerState = Candidate;
			return;
		}
	}
	OpponentPlayerState = nullptr;
}

ABoard* UBoardFunctionLibrary::GetBoardByObject(const UObject* Object)
{
	return GetBoard(Object);
}

AGoalkeeperActor* UBoardFunctionLibrary::GetGoalkeeperActor(const FBoardPlayerData& PlayerState,const bool Opponent)
{
	const auto Board = GetBoardByObject(PlayerState.PlayerState);
	const auto Goalkeepers = Board->Goalkeepers;
	for(const auto Goalkeeper : Goalkeepers)
	{
		if((Goalkeeper->GetPlayerId() == PlayerState.BoardIndex && !Opponent) ||
			(Goalkeeper->GetPlayerId() != PlayerState.BoardIndex && Opponent))
		{
			return Goalkeeper;
		}
	}
	return nullptr;
}

void UBoardFunctionLibrary::MoveUnitsToDir(AUnitActor* Unit, const bool UpDir)
{
	const auto NewSlot = UpDir ? Unit->CurrentSlot->UpSlot : Unit->CurrentSlot->DownSlot;
	if(NewSlot == nullptr) return;
	const auto OldUnit = NewSlot->AttachedUnit;
	NewSlot->AttachUnit(Unit);
	Unit->MoveToSlot(NewSlot);
	if(OldUnit) MoveUnitsToDir(OldUnit,UpDir);	
}

bool UBoardFunctionLibrary::OpponentOnSide(AUnitActor* Unit, AUnitActor* Opponent,const bool HasToBeActive)
{
	if(Opponent == nullptr || Unit == nullptr) return false;
	const auto TargetSlot = Opponent->CurrentSlot;
	return (Opponent->IsActivated() || !HasToBeActive)
		&& Opponent->GetPlayerId() != Unit->GetPlayerId()
		&& (TargetSlot->LeftSlot && TargetSlot->LeftSlot->AttachedUnit == Unit
		|| TargetSlot->RightSlot && TargetSlot->RightSlot->AttachedUnit == Unit);
}

UStatComponent* UBoardFunctionLibrary::GetStatComponent(const AActor* Actor)
{
	if(Actor == nullptr) return nullptr;
	const auto StatComponent = Actor->GetComponentByClass<UStatComponent>();
	return StatComponent;
}

ABoard* UBoardFunctionLibrary::GetBoard(const UObject* Object)
{
	const auto Actor = UGameplayStatics::GetActorOfClass(Object->GetWorld(),ABoard::StaticClass());
	const auto Board = Cast<ABoard>(Actor);
	return Board;
}

