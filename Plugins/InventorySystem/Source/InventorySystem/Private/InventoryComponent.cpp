// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

int32 UInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	FInventorySlotInfo* SlotPtr = Items.Find(SlotIndex);

	if (SlotPtr && SlotPtr->ID == InItem.ID)
	{
		return 0;
	}

	return -1;
}

void UInventoryComponent::ClearInventory()
{
	Items.Reset();
}

void UInventoryComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (Ar.IsSaveGame())
	{
		if (Ar.IsSaving())
		{
			int32 ItemsCount = Items.Num();
			Ar << ItemsCount;
			for (auto Item : Items)
			{
				Ar << Item.Key;
				Ar << Item.Value.Count;
				Ar << Item.Value.ID;
			}
		}
		else
		{
			Items.Reset();
			int32 ItemsCount;
			Ar << ItemsCount;
			int32 Key;
			FInventorySlotInfo Info;
			for (int32 i = 0; i < ItemsCount; ++i)
			{
				Ar << Key;
				Ar << Info.Count;
				Ar << Info.ID;
				Items.Add(Key, Info);
			}
		}
		
	}
}


