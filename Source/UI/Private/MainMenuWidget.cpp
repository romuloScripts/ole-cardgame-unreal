#include "MainMenuWidget.h"
#include "WidgetFunctionLibrary.h"
#include "MenuSwitcherParams.h"

void UMainMenuWidget::CreateSwitcherParams(int i, UMenuSwitcherParams* SwitcherParams)
{
	SwitcherParams = NewObject<UMenuSwitcherParams>(this);
	SwitcherParams->menuIndex = i;
	SwitcherParams->Menu_WidgetSwitcher = Menu_WidgetSwitcher;
}

void UMainMenuWidget::NativeConstruct()
{
	Menu_WidgetSwitcher->SetActiveWidgetIndex(0);
	MenuSwitcherParams = UWidgetFunctionLibrary::BindButtonsWithSwitcher(Menu_Top->TabsContainer,Menu_WidgetSwitcher);
}
