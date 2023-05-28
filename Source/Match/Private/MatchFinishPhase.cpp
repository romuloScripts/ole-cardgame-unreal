
#include "MatchFinishPhase.h"
#include "MatchHUDBase.h"

void UMatchFinishPhase::OnBegin(const FGameContext& Context)
{
	Super::OnBegin(Context);
	
	const int WinnerId = GameContext.GameState->GetWinnerPlayerId();
	const auto WinState = GameContext.GameState->GetWinState();
	for(int i=0;i < GameContext.GameControllersArray.Num();i++)
	{
		GameContext.GameControllersArray[i]->DisableAllInteractions();
		const EPlayerVictoryState PlayerWinState =
			WinState == EWinState::Draw ? EPlayerVictoryState::Draw :
			WinnerId == i ? EPlayerVictoryState::Win : EPlayerVictoryState::Lose;
		GameContext.GameControllersArray[i]->GetMatchHud()->ShowVictory(PlayerWinState);
	}
}

bool UMatchFinishPhase::EndIf()
{
	return true;
}
