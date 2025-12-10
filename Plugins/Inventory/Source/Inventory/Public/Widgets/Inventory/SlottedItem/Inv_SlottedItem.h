// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

class UInv_InventoryItem;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetGridIndex(const int32 Index) { GridIndex = Index; } ;
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; };
	void SetInventoryItem(UInv_InventoryItem* Item);
	void SetIsStackable(const bool IsStackable) { bIsStackable = IsStackable; };
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	UFUNCTION(BlueprintCallable)
	UImage* GetImage() const { return Image_Icon; }

	UFUNCTION(BlueprintCallable)
	int32 GetGridIndex() const { return GridIndex; }

	UFUNCTION(BlueprintCallable)
	FIntPoint GetGridDimensions() const { return GridDimensions; }

	UFUNCTION(BlueprintCallable)
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }

	UFUNCTION(BlueprintCallable)
	bool GetIsStackable() const { return bIsStackable; }

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	int32 GridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;

	bool bIsStackable = false;
};
