
#include "Board.h"
#include "BoardFunctionLibrary.h"
#include "DeckFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = true;
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Board"));
	SetRootComponent(WidgetComponent);
	GoalkeeperTarget = CreateDefaultSubobject<USceneComponent>(TEXT("GoalkeeperTarget"));
	GoalkeeperTarget->AttachToComponent(WidgetComponent,FAttachmentTransformRules::KeepRelativeTransform);
	GoalkeeperTarget2 = CreateDefaultSubobject<USceneComponent>(TEXT("GoalkeeperTarget2"));
	GoalkeeperTarget2->AttachToComponent(WidgetComponent,FAttachmentTransformRules::KeepRelativeTransform);
	LockerRoom = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockerRoom"));
	LockerRoom->AttachToComponent(WidgetComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

void ABoard::MoveEnd_Implementation(const int PlayerId)
{
	OnMoveEnd.Broadcast(PlayerId);
}

void ABoard::MoveBegin_Implementation(const int PlayerId)
{
	OnMoveBegin.Broadcast(PlayerId);
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
	if(!HasAuthority()) return;
	CreateSlots();
}

void ABoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoard, SlotMap);
	DOREPLIFETIME(ABoard, AllUnitsArray);
	DOREPLIFETIME(ABoard, Goalkeepers);
	DOREPLIFETIME(ABoard, BallActor);
}

void ABoard::CreateSlots()
{
	SlotMap.SetNum(Lines * Columns.Num());
	for (int Y=0; Y< Lines; Y++)
	{
		for (int X=0; X < Columns.Num(); X++)
		{
			AddSlot(FIntPoint(X,Y),Columns[X]);
		}
	}
	ConnectSlots();
}

void ABoard::AddSlot(FIntPoint Point, FBoardColumn Column)
{
	if(GetSlotAtPoint(Point)) return;
	const auto Location = GetActorLocation();
	const auto Rotation = GetActorRotation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();

	const FVector Pos = FVector(
	Location.X + Offset - Point.Y,
	Location.Y - Point.X * TilesSize.X + (TilesSize.X * Columns.Num())/2.0f - TilesSize.X/2.0f,
	Location.Z + Point.Y * TilesSize.Y - (TilesSize.Y * Lines)/2.0f + TilesSize.Y/2.0f);
	
	ABoardSlot* Slot = GetWorld()->SpawnActor<ABoardSlot>(SlotClass,Rotation.RotateVector(Pos),Rotation,SpawnParameters);
	Slot->GridId = Point;
	Slot->CardType = Column.CardType;
	Slot->PlayerId = Column.PlayerId;
	SlotMap[GetSlotArrayIndex(Slot)] = Slot;
}

void ABoard::ConnectSlots()
{
	for (const auto Slot : SlotMap)
	{
		const auto Pos = Slot->GridId;
		const auto Up = FIntPoint(Pos.X,Pos.Y-1);
		const auto Down = FIntPoint(Pos.X,Pos.Y+1);
		const auto Left = FIntPoint(Pos.X-1,Pos.Y);
		const auto Right = FIntPoint(Pos.X+1,Pos.Y);

		Slot->UpSlot = AddConnection(Up);
		Slot->DownSlot = AddConnection(Down);
		Slot->LeftSlot = AddConnection(Left);
		Slot->RightSlot = AddConnection(Right);
	}
}

ABoardSlot* ABoard::AddConnection(FIntPoint Point)
{
	if(Point.X < Columns.Num() && Point.X >= 0 && Point.Y >= 0 && Point.Y < Lines)
	{
		return GetSlotAtPoint(Point);
	}
	return nullptr;
}

ABoardSlot* ABoard::GetSlotAtPoint(FIntPoint Point)
{
	return SlotMap[Point.X + Columns.Num() * Point.Y];
}

int ABoard::GetSlotArrayIndex(const ABoardSlot* Slot) const
{
	return Slot->GridId.X + Columns.Num() * Slot->GridId.Y;
}

void ABoard::StartPlayers_Implementation(const TArray<FBoardPlayerData>& Players)
{
	if(AllUnitsArray.Num()<= 0)
	{
		SpawnSoccerPlayers(Players);
	}
	
	for (const auto Unit : AllUnitsArray)
	{
		Unit->SetBattleState();
	}
}

void ABoard::SpawnSoccerPlayers_Implementation(const TArray<FBoardPlayerData>& Players)
{
	for(int i = 0; i < Players.Num();i++)
	{
		SpawnUnits(Players[i]);
		SpawnGoalkeeper(Players[i]);
	}
}

void ABoard::StartBall_Implementation(const int PlayerId)
{
	if(!BallActor)
	{
		BallActor = GetWorld()->SpawnActor<ABallActor>(BallClass);
	}
	auto Slots = UBoardFunctionLibrary::GetMiddleColumnSlotsByPlayer(PlayerId,this);
	int ColumnOffset=0;
	int const Middle = (Slots.Num()-1)/2;
	int Id = Middle;
	AUnitActor* Unit = nullptr;
	while (Unit == nullptr && Id >= 0 && Id < Slots.Num())
	{
		Unit = Slots[Id]->AttachedUnit;
		ColumnOffset = ColumnOffset<=0 ? ColumnOffset *-1+1 : ColumnOffset *-1;
		Id = Middle + ColumnOffset;
	}

	if(Unit)
	{
		BallActor->AttachToSoccerActor(Unit,true);
	}
}

void ABoard::ResetUnitsInactiveStatus()
{
	for(const auto Unit : AllUnitsArray)
	{
		Unit->ResetPoints();
	}
	for(const auto Goalkeeper : Goalkeepers)
	{
		if(Goalkeeper->ReceivedGoal)
		{
			Goalkeeper->ResetPoints();
		}
	}
}

TArray<AUnitActor*> ABoard::GetAllUnits()
{
	return AllUnitsArray;
}

TArray<TScriptInterface<IBoardInteractable>> ABoard::GetAllInteractables()
{
	TArray<TScriptInterface<IBoardInteractable>> Interactables;
	for (auto Slot : SlotMap)
	{
		Interactables.Add(Slot);
	}
	for (auto Goalkeeper : Goalkeepers)
	{
		Interactables.Add(Goalkeeper);
	}
	return Interactables;
}

void ABoard::RemoveUnit(AUnitActor* UnitActorToRemove)
{
	AllUnitsArray.Remove(UnitActorToRemove);
}

void ABoard::Goal_Implementation(const int PlayerId)
{
	OnGoal.Broadcast(PlayerId);
}

void ABoard::SpawnGoalkeeper(const FBoardPlayerData& PlayerData)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = PlayerData.Controller;
	const auto GoalkeeperActor = GetWorld()->SpawnActor<AGoalkeeperActor>(GoalkeeperClass,SpawnParameters);
	GoalkeeperActor->Setup(PlayerData.PlayerStatus.Deck.GoalkeeperPreset,PlayerData);
	Goalkeepers.SetNum(FMath::Max(Goalkeepers.Num(),PlayerData.BoardIndex+1));
	Goalkeepers[PlayerData.BoardIndex] = GoalkeeperActor;
	AddGoalkeeperToBoard(GoalkeeperActor,PlayerData.BoardIndex == 0 ? GoalkeeperTarget: GoalkeeperTarget2,PlayerData.BoardIndex==0);
}

void ABoard::AddGoalkeeperToBoard(AGoalkeeperActor* Goalkeeper, USceneComponent* Target, bool Left)
{
	Goalkeeper->SetLocation(Target->GetComponentLocation(),Target->GetComponentRotation(),!Left);
	auto Slots = UBoardFunctionLibrary::GetSlotsByColumn(this,Left ? 0 : Columns.Num()-1);
	const int Lenght = Slots.Num();
	TArray<ABoardSlot*> Neighbors;
	for(int i=GoalkeeperSlotVerticalRange.X;i < Lenght && i <= GoalkeeperSlotVerticalRange.Y; i++)
	{
		if(Left)
			Slots[i]->LeftGoalkeeper = Goalkeeper;
		else
			Slots[i]->RightGoalkeeper = Goalkeeper;
		Neighbors.Add(Slots[i]);
	}
	Goalkeeper->SetNeighbors(Neighbors);
}

void ABoard::SpawnUnits(const FBoardPlayerData& PlayerData)
{
	auto Units = UDeckFunctionLibrary::GetUnitsCardsFromDeck(PlayerData.PlayerStatus.Deck);
	TArray<AUnitActor*> UnitArray;
	for(const auto Unit : Units)
	{
		UnitArray.Add(SpawnUnit(PlayerData, Unit));
	}
	AddUnitsByColumn(UnitArray,PlayerData.BoardIndex);
	AllUnitsArray.Append(UnitArray);
}

AUnitActor* ABoard::SpawnUnit(const FBoardPlayerData& PlayerData, UCardPreset* Preset)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = PlayerData.Controller;
	AUnitActor* Unit = GetWorld()->SpawnActor<AUnitActor>(UnitClass,FTransform(FVector::UpVector * 1000),SpawnParameters);
	Unit->Setup(Preset,PlayerData);
	return Unit;
}

void ABoard::AddUnitsByColumn(const TArray<AUnitActor*>& UnitsPlayer, const int PlayerId)
{
	for(int X=0; X< Columns.Num(); X++)
	{
		if(Columns[X].PlayerId != PlayerId) continue;
		auto SlotsArray = UBoardFunctionLibrary::GetSlotsByColumn(this,X);
		auto UnitsArray = UBoardFunctionLibrary::GetUnitsByType(UnitsPlayer,Columns[X].CardType);
		int LineOffset = FMath::Max(0, SlotsArray.Num() - UnitsArray.Num());
		LineOffset = LineOffset%2 == 0 ? LineOffset : LineOffset + FMath::RandRange(0,1);
		LineOffset /=2;
		for(int i=LineOffset, UnitId =0; i < SlotsArray.Num() && UnitId < UnitsArray.Num();i++,UnitId++)
		{
			AddUnitToSlot(UnitsArray[UnitId], SlotsArray[i]);
		}
	}
}

void ABoard::AddUnitToSlot(AUnitActor* Unit, ABoardSlot* Slot)
{
	Slot->AttachUnit(Unit);
	Unit->AttachToSlotAndTeleport(Slot);
}

