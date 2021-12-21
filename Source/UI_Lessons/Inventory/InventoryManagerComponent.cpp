// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "EquipInventoryComponent.h"
#include "InventoryCellWidget.h"
#include "InventoryWidget.h"


// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{

}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && ItemsData && InventoryWidgetClass)
	{

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->ParentInventory = InInventoryComponent;

		InventoryWidget->Init(FMath::Max(MinInventorySize, LocalInventoryComponent->GetItemsNum()));
		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropFunc);
		
		for	(const auto& Item : LocalInventoryComponent->GetItems())
		{
			auto* Data = GetItemData(Item.Value.ID);
			if (Data)
			{
				InventoryWidget->AddItem(Item.Value, *Data, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitEquip(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UInventoryWidget>(GetWorld(),EquipWidgetClass);
		EquipWidget->ParentInventory = InInventoryComponent;
		EquipWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropFunc);
		EquipWidget->AddToViewport();
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID,"") : nullptr;
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	if (From == nullptr || To == nullptr)
	{
		return;
	}

	auto* FromInventory = From->GetParentInventory();
	auto* ToInventory = To->GetParentInventory();

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	const FInventorySlotInfo FromItem = From->GetItem();
	if (FromItem.Count == 0)
	{
		return;
	}
	
	const FInventorySlotInfo ToItem = To->GetItem();

	const FInventoryItemInfo* FromInfo = GetItemData(FromItem.ID);
	const FInventoryItemInfo* ToInfo = ToItem.Count > 0 ? GetItemData(ToItem.ID) : nullptr;
	
	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(To->IndexInInventory, *FromInfo);
	
	UE_LOG(LogTemp, Warning, TEXT("ToItemAmount = %d"), ToItemAmount);
	
	if (ToItemAmount == 0 )
	{
		return;
	}
	
	FInventorySlotInfo NewFromItem = ToItem;
	FInventorySlotInfo NewToItem = FromItem;

	if (ToItemAmount > 0)
	{
		if (NewFromItem.ID == NewToItem.ID)
		{
			NewToItem.Count = FMath::Max(ToItemAmount, FromItem.Count);
			if (FromItem.Count <= NewToItem.Count)
			{
				NewFromItem.ID = NewToItem.ID;
				NewFromItem.Count = FromItem.Count - NewToItem.Count;
			}
		}

	}


	const FInventoryItemInfo* NewFromInfo = NewFromItem.Count > 0 ? GetItemData(NewFromItem.ID) : nullptr;
	const FInventoryItemInfo* NewToInfo = GetItemData(NewToItem.ID);

	if (Cast<UEquipInventoryComponent>(From->GetParentInventory()) && NewFromInfo)
	{
		if (NewToInfo->Type == EItemType::It_Equipment && NewToInfo->EquipSLot == NewFromInfo->EquipSLot)
		{
			From->Clear();
			From->AddItem(NewFromItem, *NewFromInfo);

			To->Clear();
			To->AddItem(NewToItem, *NewToInfo);

			FromInventory->SetItem(From->IndexInInventory, NewFromItem);
			ToInventory->SetItem(To->IndexInInventory, NewToItem);
		} 
	}
	else
	{
		From->Clear();
		if (NewFromInfo)
		{
			From->AddItem(NewFromItem, *NewFromInfo);
		}

		To->Clear();
		To->AddItem(NewToItem, *NewToInfo);

		FromInventory->SetItem(From->IndexInInventory, NewFromItem);
		ToInventory->SetItem(To->IndexInInventory, NewToItem);
	}
	

}




