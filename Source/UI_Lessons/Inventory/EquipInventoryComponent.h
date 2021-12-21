// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"

#include "EquipInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UI_LESSONS_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	UEquipInventoryComponent();

	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSLot> EquipSlots;

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem) override;
};
