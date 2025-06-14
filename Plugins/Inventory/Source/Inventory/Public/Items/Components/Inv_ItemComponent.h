
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_ItemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable)
class INVENTORY_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInv_ItemComponent();

	UFUNCTION(BlueprintCallable)
	FString GetPickupMessage() const { return PickupMessage; }
protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Inventory")
	FString PickupMessage;
};
