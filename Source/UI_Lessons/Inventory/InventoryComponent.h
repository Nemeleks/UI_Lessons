// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UI_LESSONS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TMap<int32, FInventorySlotInfo> Items;

public:

	const FInventorySlotInfo* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); }

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

	virtual void DeleteItem(int32 SlotIndex);

	const TMap<int32, FInventorySlotInfo>& GetItems() const {return Items;}

	int32 GetItemsNum() const {return Items.Num();}
};
