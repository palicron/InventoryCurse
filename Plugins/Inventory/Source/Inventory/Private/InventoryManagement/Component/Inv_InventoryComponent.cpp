
#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "Inventory/Public/Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Blueprint/UserWidget.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
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
}



