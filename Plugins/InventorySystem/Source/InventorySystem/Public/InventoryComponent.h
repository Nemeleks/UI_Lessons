// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "InventoryItems")
	TMap<int32, FInventorySlotInfo> Items;

public:

	const FInventorySlotInfo* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); }

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

	virtual void ClearItem(int32 SlotIndex);

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem);

	const TMap<int32, FInventorySlotInfo>& GetItems() const {return Items;}

	int32 GetItemsNum() const {return Items.Num();}
	
	void ClearInventory();

	virtual void Serialize(FArchive& Ar) override;
};
