#pragma once

#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemManifest.generated.h"


/**
 * The item Manifest contains all of the necessary data
 * for creating a new Inventory Item
 */

class UInv_InventoryItem;
enum class EInv_ItemCategory : uint8;

USTRUCT(BlueprintType)
struct INVENTORY_API FInv_ItemManifest
{
	GENERATED_BODY()

public:

	UInv_InventoryItem* Manifest(UObject* NewOuter);
	
	EInv_ItemCategory GetCategory() const { return ItemCategory; }

private:
	UPROPERTY(EditAnywhere, Category="Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};
};



