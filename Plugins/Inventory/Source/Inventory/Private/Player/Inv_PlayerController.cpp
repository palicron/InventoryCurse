// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Inv_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Widgets/HUD/Inv_HUDWidget.h"
#include "Components/InputComponent.h"
#include "Interaction/Inv_Highlightable.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceDistance = 1000.f;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForItem();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultIMCs)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	CreateHUDWidget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(PrimaryInteractAction,ETriggerEvent::Started,this,&AInv_PlayerController::PrimaryInteract);
}

void AInv_PlayerController::PrimaryInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Primary Interact"));
}


void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController())
	{
		return;
	}

	HUDWidget = CreateWidget<UInv_HUDWidget>(GetWorld(), HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AInv_PlayerController::TraceForItem()
{
	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}

	FVector2D ViewPortSize;
	GEngine->GameViewport->GetViewportSize(ViewPortSize);

	const FVector2D ViewPortCenter = ViewPortSize * 0.5f;

	FVector ViewPortLocation;
	FVector ViewPortDirection;

	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewPortCenter, ViewPortLocation, ViewPortDirection))
	{
		return;
	}

	const FVector TraceEnd = ViewPortLocation + (ViewPortDirection * TraceDistance);
	FHitResult OutHit;

	GetWorld()->LineTraceSingleByChannel(OutHit, ViewPortLocation, TraceEnd, ItemTraceChannel);
	
	LastActor = ThisActor;
	ThisActor = OutHit.GetActor();

	if (!ThisActor.IsValid())
	{
		if (HUDWidget)
		{
			HUDWidget->HidePickUpMessage();
		}
	}
	
	if (ThisActor == LastActor)
	{
		return;
	}

	if (ThisActor.IsValid())
	{
		const UInv_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UInv_ItemComponent>();
		
		if (IInv_Highlightable* Highlightable = ThisActor->FindComponentByInterface<IInv_Highlightable>())
		{
			
			IInv_Highlightable::Execute_Highlight(Cast<UObject>(Highlightable));
		}
		
		if (!ItemComponent)
		{
			return;
		}

		if (HUDWidget)
		{
			HUDWidget->ShowPickUpMessage(ItemComponent->GetPickupMessage());
		}

		
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *ThisActor->GetName());
	}

	if (LastActor.IsValid())
	{
		if (IInv_Highlightable* Highlightable = LastActor->FindComponentByInterface<IInv_Highlightable>())
		{
			IInv_Highlightable::Execute_Unhighlight(Cast<UObject>(Highlightable));
		}
		UE_LOG(LogTemp, Warning, TEXT("Stopt racin last Actor: %s"), *LastActor->GetName());
	}
	
}

