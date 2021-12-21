// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"


UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSLot::Es_Head);
	EquipSlots.Add(1, EEquipSLot::Es_Body);
	EquipSlots.Add(2, EEquipSLot::Es_LeftHand);
	EquipSlots.Add(3, EEquipSLot::Es_RightHand);
	EquipSlots.Add(4, EEquipSLot::Es_Feet);
	
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	EEquipSLot* EquipSlotPtr = EquipSlots.Find(SlotIndex);
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
