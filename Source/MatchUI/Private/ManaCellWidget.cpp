#include "ManaCellWidget.h"

void UManaCellWidget::UpdateState(EManaCellState NewState)
{
	if(NewState == EManaCellState::ReturnNormalState)
	{
		if(state == EManaCellState::WillSpend)
		{
			NewState = EManaCellState::Full;
		}else
		{
			return;
		}
	}
	if(NewState == state) return;
	state = NewState;
	switch (state)
	{
		case EManaCellState::Empty:
			StopAllAnimations();
			PlayAnimation(Anim_Empty);
			break;
		case EManaCellState::Spent:
			StopAllAnimations();
			PlayAnimation(Anim_Spend);
			break;
		case EManaCellState::WillSpend:
			manaBall->SetRenderOpacity(1);
			StopAllAnimations();
			PlayAnimation(Anim_Jumping,0,0);
			break;
		case EManaCellState::Full:
		default:
			manaBall->SetRenderOpacity(1);
			StopAllAnimations();
			PlayAnimation(Anim_Idle);
		break; 
	}
}
