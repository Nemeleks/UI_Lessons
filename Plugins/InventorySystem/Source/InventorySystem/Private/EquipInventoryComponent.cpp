// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"
#include "GameFramework/Actor.h"

#include "EquipInterface.h"


UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::Es_Head);
	EquipSlots.Add(1, EEquipSlot::Es_Body);
	EquipSlots.Add(2, EEquipSlot::Es_LeftHand);
	EquipSlots.Add(3, EEquipSlot::Es_RightHand);
	EquipSlots.Add(4, EEquipSlot::Es_Feet);
	
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	EEquipSlot* EquipSlotPtr = EquipSlots.Find(SlotIndex);
	UE_LOG(LogTemp,Warning,TEXT("OK"));

	if (InItem.Type == EItemType::It_Equipment)
	{
		UE_LOG(LogTemp,Warning,TEXT("InItem.Type == EItemType::It_Equipment"));
	}
	
	if (EquipSlotPtr)
	{
		UE_LOG(LogTemp,Warning,TEXT("EquipSlotPtr"));
		UE_LOG(LogTemp,Warning,TEXT("EquipSlotPtr EquipSlot = %d"), *EquipSlotPtr);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("EquipSlotPtr NULLPTR"));
	}
	

	UE_LOG(LogTemp,Warning,TEXT("EquipSlot = %d"), InItem.EquipSLot);
	

	if (InItem.Type == EItemType::It_Equipment && EquipSlotPtr && *EquipSlotPtr == InItem.EquipSLot)
	{
		return 1;
	}

	return 0;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	auto* InventoryOwner = GetOwner();

	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}
	
	EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);

	if (auto* ItemInfo = GetItem(SlotIndex))
	{
		IEquipInterface::Execute_UnEquipItem(InventoryOwner, EquipSlot, ItemInfo->ID);
	}
	
	Super::SetItem(SlotIndex, Item);

	IEquipInterface::Execute_EquipItem(InventoryOwner, EquipSlot, Item.ID);
}

void UEquipInventoryComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();

	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::ClearItem(SlotIndex);
		return;
	}
	
	EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
	if (auto* ItemInfo = GetItem(SlotIndex))
	{
		IEquipInterface::Execute_UnEquipItem(InventoryOwner, EquipSlot, ItemInfo->ID);
	}
	
	Super::ClearItem(SlotIndex);
}
