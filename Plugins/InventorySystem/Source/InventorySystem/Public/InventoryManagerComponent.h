// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	void InitEquip(UInventoryComponent* InInventoryComponent);

	const FInventoryItemInfo* GetItemData(const FName& InID) const;

	void DeInit();

	bool IsInitialized();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "InventoryManager")
	UInventoryComponent* LocalInventoryComponent;
	

	UPROPERTY(EditAnywhere, Category = "InventoryManager")
	UDataTable* ItemsData;

	
	UPROPERTY(EditAnywhere, Category = "InventoryManager")
	int32 MinInventorySize = 20;

	UPROPERTY(EditDefaultsOnly, Category = "InventoryManager")
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, Category = "InventoryManager")
	TSubclassOf<class UInventoryWidget>  InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "InventoryManager")
	class UInventoryWidget* EquipWidget;

	UPROPERTY(EditAnywhere, Category = "InventoryManager")
	TSubclassOf<class UInventoryWidget>  EquipWidgetClass;
	
	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);

private:
	bool bIsInventoryWidget = false;
	bool bIsEquipWidget = false;
};