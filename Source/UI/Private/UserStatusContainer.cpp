#include "UserStatusContainer.h"

#include "Blueprint/WidgetTree.h"
#include "UserStatus.h"
#include "WidgetFunctionLibrary.h"

void UUserStatusContainer::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateUserStatus(UserStatus,Customization);
}

void UUserStatusContainer::NativeConstruct()
{
	const auto StatusController = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UUserStatusController>();
	if(UserStatusController == nullptr && StatusController != nullptr)
	{
		SetUserStatusController(StatusController);
	}
	Super::NativeConstruct();
}

void UUserStatusContainer::NativeDestruct()
{
	if(UserStatusController != nullptr)
	{
		UserStatusController->OnUserStatusChangedDelegate.RemoveDynamic(this,&UUserStatusContainer::UpdateUserStatus);
		UserStatusController = nullptr;
	}
	Super::NativeDestruct();
}

void UUserStatusContainer::UpdateUserStatus(const FUserStatus& NewUserStatus,const FCustomizationData& NewCustomization)
{
	if(!IsVisible()) return;
	UserStatus = NewUserStatus;
	Customization = NewCustomization;
	UpdateContent();
	OnUpdateContent();
}

void UUserStatusContainer::SetUserStatusController(UUserStatusController* NewUserStatusController)
{
	if(NewUserStatusController == nullptr) return;
	UserStatusController = NewUserStatusController;
	UserStatusController->OnUserStatusChangedDelegate.AddDynamic(this,&UUserStatusContainer::UpdateUserStatus);
	UpdateUserStatus(UserStatusController->UserStatus,UserStatusController->GetCurrentCustomization());
}

void UUserStatusContainer::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if(!IsVisible()) return;
	if(UserStatusController != nullptr)
		UpdateUserStatus(UserStatusController->UserStatus,UserStatusController->GetCurrentCustomization());
	else
		UpdateUserStatus(UserStatus,Customization);
}

void UUserStatusContainer::UpdateContent()
{
	if(UpdatePresetsOnChildren) UWidgetFunctionLibrary::UpdateUserInWidget(this,Customization);
}

void UUserStatusContainer::OnUpdateContent_Implementation()
{
	
}
