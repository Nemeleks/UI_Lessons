// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

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

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InID,"") : nullptr;
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	FInventorySlotInfo FromItem = From->GetItem();
	FInventorySlotInfo ToItem = To->GetItem();

	From->Clear();
	To->Clear();
	
	To->AddItem(FromItem, *GetItemData(FromItem.ID));

	if (!ToItem.ID.IsNone())
	{
		From->AddItem(ToItem, *GetItemData(ToItem.ID));
	}

	
}




