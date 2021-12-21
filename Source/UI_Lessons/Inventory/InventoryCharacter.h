// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipInterface.h"
#include "GameFramework/Character.h"
#include "InventoryItem.h"
#include "InventoryCharacter.generated.h"


UCLASS()
class UI_LESSONS_API AInventoryCharacter : public ACharacter, public IEquipInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryCharacter();

	void SetClassInventory(UDataTable* InventoryData) {StartInventory = InventoryData;}

	virtual void EquipItem_Implementation(EEquipSlot Slot, FName ItemID) override;
	
	virtual void UnEquipItem_Implementation(EEquipSlot Slot, FName ItemID) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	class UInventoryComponent* LocalInventory;

	UPROPERTY(VisibleDefaultsOnly)
	class UEquipInventoryComponent* EquipInventory;
	
	UPROPERTY(EditDefaultsOnly)
	class UInventoryManagerComponent* LocalInventoryManager;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StartInventory;

	UStaticMeshComponent* GetEquipComponent(EEquipSlot EquipSlot);

	
};
