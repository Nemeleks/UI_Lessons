// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryCharacter.h"

#include "EquipInventoryComponent.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"



// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	EquipInventory = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	LocalInventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("LocalInventoryManager");


}

void AInventoryCharacter::EquipItem_Implementation(EEquipSlot Slot, FName ItemID)
{
	//IEquipInterface::EquipItem_Implementation(Slot, ItemID);

	UStaticMeshComponent* Comp = GetEquipComponent(Slot);

	if (Comp)
	{
		UE_LOG(LogTemp, Error,TEXT("Problem"));
		auto* Info = LocalInventoryManager->GetItemData(ItemID);
		if (Info)
		{
			Comp->SetStaticMesh(Info->Mesh.LoadSynchronous());
			Comp->SetHiddenInGame(false);
		}
		
		//LocalArmor += Info.Armor;
	}
}

void AInventoryCharacter::UnEquipItem_Implementation(EEquipSlot Slot, FName ItemID)
{
	IEquipInterface::UnEquipItem_Implementation(Slot, ItemID);

	 UStaticMeshComponent* Comp = GetEquipComponent(Slot);
	
	 if (Comp)
	 {
	 	Comp->SetStaticMesh(nullptr);
	 	Comp->SetHiddenInGame(true);
	
	 	//LocalArmor -= Info.Armor;
	 }
}

void AInventoryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("InventoryKey", IE_Pressed, this, &ThisClass::OpenCloseInventory);
	}
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
	

}

void AInventoryCharacter::OpenCloseInventory()
{
	if (LocalInventoryManager->IsInitialized())
	{
		LocalInventoryManager->DeInit();
	}
	else
	{
		LocalInventoryManager->Init(LocalInventory);
		LocalInventoryManager->InitEquip(EquipInventory);
	}
}

UStaticMeshComponent* AInventoryCharacter::GetEquipComponent(EEquipSlot EquipSlot)
{
	FName Tag;

	switch (EquipSlot)
	{
	case EEquipSlot::Es_Head:
		Tag = "Head";
		break;

	case EEquipSlot::Es_Body:
		Tag = "Body";
		break;

	default:
		return nullptr;
	}

	TArray<UActorComponent*> Found = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);

	return Found.Num() > 0 ? Cast<UStaticMeshComponent>(Found[0]) : nullptr; 
}

