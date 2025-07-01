#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory: uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability()
	{
	}

	FInv_SlotAvailability(const int32 ItemIndex, const int32 AmountToFill, const bool bItemAtIndex): Index(ItemIndex), AmountToFill(AmountToFill), bItemAtIndex(bItemAtIndex)
	{
	}

	int32 Index = INDEX_NONE;

	int32 AmountToFill = 0;

	UPROPERTY()
	bool bItemAtIndex = false;
};

USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()

	FInv_SlotAvailabilityResult()
	{
	}

	int32 TotalRoomToFill = 0;

	int32 Remainder = 0;

	bool bStackable = false;

	TArray<FInv_SlotAvailability> SlotAvailability;

	TWeakObjectPtr<UInv_InventoryItem> Items;
};


