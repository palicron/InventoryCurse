
#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "Inventory/Public/Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Blueprint/UserWidget.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ConstructInventory();
}


void UInv_InventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(),TEXT("Inventory Component should have a Player Controller As Owner "));

	if (!OwningController->IsLocalController())
	{
		return;
	}

	InventoryMenu = CreateWidget<UInv_InventoryBase>(OwningController.Get(), InventoryMenuClass);
	InventoryMenu->AddToViewport();
	CloseInventoryMenu();
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	if (bIsInventoryMenuOpen)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
	}
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	if (!InventoryMenu)
	{
		return;
	}

	InventoryMenu->SetVisibility(ESlateVisibility::Visible);
	bIsInventoryMenuOpen = true;
	if (!OwningController.IsValid())
	{
		return;
	}

	FInputModeGameAndUI InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(true);
	
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	if (!InventoryMenu)
	{
		return;
	}

	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	bIsInventoryMenuOpen = false;

	if (!OwningController.IsValid())
	{
		return;
	}

	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);
}



