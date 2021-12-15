// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UI_LESSONS_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	const FInventoryItemInfo* GetItemData(const FName& InID) const;

protected:

	UPROPERTY()
	UInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
	UDataTable* ItemsData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget>  InventoryWidgetClass;

	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;

	UPROPERTY()
	class UInventoryWidget* InventoryWidget;

	void OnItemDropFunc(UInventoryCellWidget* From, UInventoryCellWidget* To);
};