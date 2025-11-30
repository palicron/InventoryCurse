#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_ItemFragment.generated.h"


USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ItemFragment()
	{
	}

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	FInv_ItemFragment(const FInv_ItemFragment& Other) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment& Other) = default;
	FInv_ItemFragment(FInv_ItemFragment&& Other) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&& Other) = default;

	virtual ~FInv_ItemFragment()
	{
	}

private:
	UPROPERTY(EditAnywhere, Category=" Inventory")
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

public:
	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(const FIntPoint& NewGridSize) { GridSize = NewGridSize; }

	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(const float NewGridPadding) { GridPadding = NewGridPadding; }
private:
	UPROPERTY(EditAnywhere, Category="Inventory")
	FIntPoint GridSize{1, 1};

	float GridPadding{0.f};
};

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetIcon() const { return Icon; }
	void SetIcon(UTexture2D* NewIcon) { Icon = NewIcon; }

	FVector2D GetIconSize() const { return IconSize; }

private:
	UPROPERTY(EditAnywhere, Category="Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};

	UPROPERTY(EditAnywhere, Category="Inventory")
	FVector2D IconSize{50.f, 50.f};
};
