// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItem.generated.h"

UENUM()
enum class EItemType : uint8
{
	It_Misc,
	It_Currency,
	It_Equipment,
	It_Consumable
};

UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Uncommon,
	Ir_Rare,
	Ir_Epic
};

UENUM()
enum class EEquipSlot : uint8
{
	Es_Head,
	Es_Body,
	Es_LeftHand,
	Es_RightHand,
	Es_Feet
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, class UInventoryCellWidget* /*from*/, class UInventoryCellWidget* /*to*/)

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "General")
	FName ID = NAME_None;

	UPROPERTY(EditAnywhere, Category = "General")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "General")
	FText Description;

	UPROPERTY(EditAnywhere, Category = "Type")
	EItemType Type;

	UPROPERTY(EditAnywhere, Category = "Type")
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, Category = "Type")
	EEquipSlot EquipSLot;

	UPROPERTY(EditAnywhere, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, Category = "Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 Damage;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 Armor;
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 Intelligence;

};

USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	int32 Count;
	
};