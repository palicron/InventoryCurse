// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

struct FInv_GridFragment;
class UInv_SlottedItem;
struct FInv_ItemManifest;
class UInv_ItemComponent;
class UInv_InventoryComponent;
class UCanvasPanel;
class UInv_GridSlot;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Inventory")
	EInv_ItemCategory GetItemCategory() const { return ItemCategory; }

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void AddItem(UInv_InventoryItem* Item);
	
	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_ItemComponent* ItemComponent) const;

protected:

	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	TSubclassOf<UInv_GridSlot> GridSlotClass;

	TArray<TObjectPtr<UInv_GridSlot>> GridSlots;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	EInv_ItemCategory ItemCategory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<UInv_SlottedItem> SlottedItemClass;

	UPROPERTY()
	TMap<int32, TObjectPtr<UInv_SlottedItem>> SlottedItems;
	
	void ConstructGrid();

	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_InventoryItem* Item) const;
	void SetSlottedItemImage(const FInv_GridFragment* GridFragmentPtr, const FInv_ImageFragment* ImageFragmentPtr, const UInv_SlottedItem* SlottedItem);
	FInv_SlotAvailabilityResult HasRoomForItem(const FInv_ItemManifest& Manifest) const;

private:

	bool MatchesCategory(const UInv_InventoryItem* Item) const;

	void AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem);

	FVector2D GetDrawSize(const FInv_GridFragment* GridFragment) const;
	
	UInv_SlottedItem*  CreateSlottedItem(UInv_InventoryItem* Item, int32 Index, bool bStackable, int32 StackAmount, const FInv_GridFragment* GridFragmentPtr, const FInv_ImageFragment* ImageFragmentPtr);

	void AddItemToIndex(UInv_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount = 0);

	void AddSlottedItemToCanvas(const int32 Index, const FInv_GridFragment* GridFragment,UInv_SlottedItem* SlottedItem) const;

	void UpdateGridSlots(UInv_InventoryItem* Item, const int32 Index);
};
