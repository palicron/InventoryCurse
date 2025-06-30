// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_InfoMessage.h"

#include "Components/TextBlock.h"

void UInv_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Message->SetText(FText::FromString(""));
	BP_MessageHide();
}

void UInv_InfoMessage::SetMessage(const FText& Message)
{
	Text_Message->SetText(Message);

	if (!bIsMessageActive)
	{
		BP_MessageShown();
	}
	else
	{
		BP_MessageHideRepeat();
	}

	bIsMessageActive = true;

	GetWorld()->GetTimerManager().SetTimer(MessageTimer, [&]()
	{
		bIsMessageActive = false;
		BP_MessageHide();
	}, MessageLifeTime, false);
}
