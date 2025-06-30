// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUD/Inv_HUDWidget.h"

#include "Inv_InfoMessage.h"
#include "InventoryManagement/Component/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"

void UInv_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer()))
	{
		InventoryComponent->NoRoomInInventoryDelegate.AddDynamic(this,&UInv_HUDWidget::OnNoRoom);
	}
}

void UInv_HUDWidget::OnNoRoom()
{
	if (!InfoMessage)
	{
		return;
	}

	InfoMessage->SetMessage(FText::FromString("No room in inventory"));
}
