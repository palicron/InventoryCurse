﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChangeSignature, UInv_InventoryItem*, Item);

class UInv_InventoryBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInv_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	void ToggleInventoryMenu();

	FInventoryItemChangeSignature OnItemAddedDelegate;

	FInventoryItemChangeSignature OnItemRemoveDelegate;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	TSubclassOf<UInv_InventoryBase> InventoryMenuClass;

private:

	bool bIsInventoryMenuOpen;

	void OpenInventoryMenu();

	void CloseInventoryMenu();
	
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryBase> InventoryMenu;
	
	void ConstructInventory();

	
};
