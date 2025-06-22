// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

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
protected:

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
	
	void ConstructGrid();


	
};
