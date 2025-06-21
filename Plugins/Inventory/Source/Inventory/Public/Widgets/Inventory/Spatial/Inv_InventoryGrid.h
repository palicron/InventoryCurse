// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

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
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	EInv_ItemCategory ItemCategory;
};
