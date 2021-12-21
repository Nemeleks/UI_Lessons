// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	DeleteItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::DeleteItem(int32 SlotIndex)
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
