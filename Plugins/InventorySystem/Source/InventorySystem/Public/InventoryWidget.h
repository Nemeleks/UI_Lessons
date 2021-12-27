// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY(EditDefaultsOnly, Category = "InventoryWidget")
	class UInventoryComponent* ParentInventory;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "InventoryWidget")
	int32 ItemsInRow = 5;

	UPROPERTY(EditDefaultsOnly, Category = "InventoryWidget")
	TSubclassOf<class UInventoryCellWidget> CellWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "InventoryWidget")
	class UUniformGridPanel* CellsPanel;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Category = "InventoryWidget")
	class UInventoryCellWidget* GoldCell;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget")
	TArray<class UInventoryCellWidget*> CellWidgets;

	class UInventoryCellWidget* CreateCell();

	void InitCell(UInventoryCellWidget* NewCell);

	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
	
};
