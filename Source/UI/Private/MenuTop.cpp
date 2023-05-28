// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTop.h"

#include "DeckFunctionLibrary.h"

void UMenuTop::UpdateContent()
{
	FFormatNamedArguments Args;
	Args.Add("LevelNumber",UserStatus.Level);
	Text_UserLevel->SetText(FText::Format(NSLOCTEXT("Ole","Level","Level {LevelNumber}"),Args));
	
	Emblem->UpdateEmblem(Customization.Emblem);
	Emblem->UpdateColor(Customization.ColorPalette);
}

void UMenuTop::NativeConstruct()
{
	Super::NativeConstruct();
	SelectionController = NewObject<USelectionController>();
	SelectionController->InitSelectablePanel(TabsContainer);
	MainMenuButton->OnClicked.AddDynamic(SelectionController,&USelectionController::UnselectAll);
	Text_UserName->SetText(FText::FromName(UDeckFunctionLibrary::GetPlayerName(GetWorld()->GetFirstLocalPlayerFromController())));
}
