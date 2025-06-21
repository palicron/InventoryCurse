﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInv_InventoryComponent;
class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AInv_PlayerController();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
	
private:

	UFUNCTION()
	void PrimaryInteract();
	
	void TraceForItem();

	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly,Category= "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;

	void CreateHUDWidget();
};
