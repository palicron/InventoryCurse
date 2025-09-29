
#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "Inventory/Public/Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	bIsInventoryMenuOpen = false;
}


void UInv_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj))
	{
		AddReplicatedSubObject(SubObj);
	}
}

void UInv_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInv_InventoryComponent,InventoryList);
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

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* Item)
{
	FInv_SlotAvailabilityResult Result = InventoryMenu->HasRoomForItem(Item);

	if (Result.TotalRoomToFill == 0)
	{
		NoRoomInInventoryDelegate.Broadcast();
		return;
	}

	if (Result.Items.IsValid() && Result.bStackable)
	{
		Server_AddStacksToItem(Item, Result.TotalRoomToFill, Result.bStackable ? Result.TotalRoomToFill : 0);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		Server_AddNewItem(Item, Result.TotalRoomToFill);
	}

	//TODO: Add Items to the inventory
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* ItemComponent,const int32 StackCount)
{
	UInv_InventoryItem* NewItem =  InventoryList.AddEntry(ItemComponent);

	//TODO Tell the owner to destroy it owning actor 
}

void UInv_InventoryComponent::Server_AddStacksToItem_Implementation(UInv_ItemComponent* ItemComponent, const int32 StackCount, const int32 Remainder)
{
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

