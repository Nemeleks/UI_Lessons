// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryCharacter.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"



// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	LocalInventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("LocalInventoryManager");


}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StartInventory)
	{
		TArray<FInventorySlotInfo*> Slots;
		StartInventory->GetAllRows<FInventorySlotInfo>("", Slots);

		for	(int32 i = 0; i < Slots.Num(); i++)
		{
			LocalInventory->SetItem(i, *Slots[i]);
		}
	}
	
	LocalInventoryManager->Init(LocalInventory);
}

