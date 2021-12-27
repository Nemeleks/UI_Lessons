// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryCellWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "CellWidget")
	class UImage* ItemImage;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "CellWidget")
	class UTextBlock* CountText;

	bool bHasItem;

	UPROPERTY(EditDefaultsOnly, Category = "CellWidget")
	FInventorySlotInfo Item;

	UPROPERTY(EditDefaultsOnly, Category = "CellWidget")
	UTexture2D* CurrentTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CellWidget")
	TSubclassOf<UInventoryCellWidget> DragWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "CellWidget")
	class UInventoryWidget*  ParentInventoryWidget;


public:
	bool HasItem() const { return bHasItem; }

	bool AddItem (const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info);

	void Clear();

	const FInventorySlotInfo& GetItem() const { return Item; }

	UPROPERTY(EditAnywhere, Category = "CellWidget")
	int32 IndexInInventory = INDEX_NONE;

	FOnItemDrop OnItemDrop;

	UInventoryWidget* GetParentInventoryWidget() const { return ParentInventoryWidget;}
	void SetParentInventoryWidget(UInventoryWidget* ParentWidget) { ParentInventoryWidget = ParentWidget; }

	class UInventoryComponent* GetParentInventory() const;

protected:
	

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere, Category = "CellWidget")
	bool bCanDrag = true;
};
