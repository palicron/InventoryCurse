#include "InventoryManagement/FastArray/Inv_FastArray.h"

#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "Items/Inv_InventoryItem.h"


void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	if (const UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(OwnerComponent))
	{
		for (const int32 Index : RemovedIndices)
		{
			IC->OnItemRemoveDelegate.Broadcast(Entries[Index].Item);
		}
	}
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	if (const UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(OwnerComponent))
	{
		for (const int32 Index : AddedIndices)
		{
			IC->OnItemAddedDelegate.Broadcast(Entries[Index].Item);
		}
	}
}

TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetAllItems()
{
	TArray< UInv_InventoryItem*> Results;

	Results.Reserve(Entries.Num());

	for (const FInv_InventoryEntry& Entry : Entries)
	{
		if (Entry.Item)
		{
			Results.Add(Entry.Item);
		}
	}

	return Results;
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* ItemComponent)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	UInv_InventoryComponent* InvC = Cast<UInv_InventoryComponent>(OwnerComponent);

	if (!InvC)
	{
		return nullptr;
	}

	FInv_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = ItemComponent->GetItemManifest().Manifest(OwningActor);

	InvC->AddRepSubObj(NewEntry.Item);
	MarkItemDirty(NewEntry);
	return NewEntry.Item;
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* Item)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();

	check(OwningActor->HasAuthority());
	
	FInv_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;

	MarkItemDirty(NewEntry);

	return NewEntry.Item;
}


void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* Item)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FInv_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
			break;
		}
	}
}
