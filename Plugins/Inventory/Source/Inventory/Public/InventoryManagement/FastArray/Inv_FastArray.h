﻿#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Inv_FastArray.generated.h"


class UInv_InventoryComponent;
class UInv_InventoryItem;

/**
 * A single entry in a inventory
 */
USTRUCT(BlueprintType)
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FInv_InventoryEntry()
	{
	}

private:
	friend UInv_InventoryComponent;
	friend struct FInv_InventoryFastArray;

	UPROPERTY()
	TObjectPtr<UInv_InventoryItem> Item = nullptr;
};

/**
 * List of inventory items
 */
USTRUCT(BlueprintType)
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

	FInv_InventoryFastArray():OwnerComponent(nullptr){}
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent):OwnerComponent(InOwnerComponent){}

	TArray<FInv_InventoryEntry>& GetAllItems() { return Entries; }

#pragma region FFastArraySerializer

	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(Entries, DeltaParams, *this);
	}

	UInv_InventoryItem* AddEntry(UInv_InventoryComponent* ItemComponent);
	UInv_InventoryItem* AddEntry(UInv_InventoryItem* Item);

	void RemoveEntry(UInv_InventoryItem* Item);
#pragma endregionFFastArraySerializer
	

private:

	friend UInv_InventoryComponent;
	
	//Replicated List of items
	UPROPERTY()
	TArray<FInv_InventoryEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};