// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellWidget.h"
#include "InventoryDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
		CurrentTexture = Info.Icon.LoadSynchronous();
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}

	bHasItem = true;
	Item = InSlot;
	return true;
}

void UInventoryCellWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}

	bHasItem = false;
	Item = FInventorySlotInfo();
}

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(
		UInventoryDragDropOperation::StaticClass());
	
	if (OutOperation) 
	{
		auto InventoryDragDropOperation = 
			Cast<UInventoryDragDropOperation>(OutOperation);
		
		if (InventoryDragDropOperation)
		{
			InventoryDragDropOperation->SourceCell = this;
		//	InventoryDragDropOperation->DefaultDragVisual = this;
		}
	}
	
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{

	auto InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(InOperation);
	
	if (InventoryDragDropOperation && InventoryDragDropOperation->SourceCell != this)
	{

		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->SourceCell, this);
			GLog->Log(ELogVerbosity::Warning, TEXT("OnDrop TRUE!"));
			return true;
			
		}
	}
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
