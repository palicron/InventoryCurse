// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "UObject/Object.h"
#include "Inv_InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; };

	void SetItemManifest(const FInv_ItemManifest& Manifest);

	UFUNCTION(BlueprintCallable)
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }

	UFUNCTION(BlueprintCallable)
	FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }
private:
	UPROPERTY(VisibleAnywhere, Replicated, meta = (BaseStruct = "/Script/Inventory.Inv_ItemManifest"))
	FInstancedStruct ItemManifest;
};

template <typename FragmentType>
const FragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& FragmentTag) 
{
	if (!Item)
	{
		return nullptr;
	}

	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWhitTag<FragmentType>(FragmentTag);
}
