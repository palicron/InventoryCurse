#pragma once

#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTagContainer.h"
#include "Items/Fragments/Inv_ItemFragment.h"
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

	FGameplayTag GetItemType() const { return ItemType; }

	template<typename T> requires std::derived_from<T, FInv_ItemFragment>
	const T* GetFragmentOfTypeWhitTag(const FGameplayTag& FragmentTag) const;
	

private:
	UPROPERTY(EditAnywhere, Category=" Inventory", meta =(ExcludeBaseStruct))
	TArray<TInstancedStruct<FInv_ItemFragment>> ItemFragments;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	EInv_ItemCategory ItemCategory{EInv_ItemCategory::None};

	UPROPERTY(EditAnywhere)
	FGameplayTag ItemType;
	
};

template <typename T>
	requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentOfTypeWhitTag(const FGameplayTag& FragmentTag) const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : ItemFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			if (FragmentPtr->GetFragmentTag().MatchesTagExact(FragmentTag))
			{
				return FragmentPtr;
			}
		}
	}
	return nullptr;
}

