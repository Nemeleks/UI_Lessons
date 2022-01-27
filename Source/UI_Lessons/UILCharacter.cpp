// Fill out your copyright notice in the Description page of Project Settings.


#include "UILCharacter.h"

#include "EquipInventoryComponent.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"
#include "QuestListComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Sets default values
AUILCharacter::AUILCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestListComp = CreateDefaultSubobject<UQuestListComponent>(TEXT("QuestListComponent"));
	LocalInventory = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	EquipInventory = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	LocalInventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("LocalInventoryManager");
}

void AUILCharacter::EquipItem_Implementation(EEquipSlot Slot, FName ItemID)
{
	IEquipInterface::EquipItem_Implementation(Slot, ItemID);

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

void AUILCharacter::UnEquipItem_Implementation(EEquipSlot Slot, FName ItemID)
{
	IEquipInterface::UnEquipItem_Implementation(Slot, ItemID);

	IEquipInterface::UnEquipItem_Implementation(Slot, ItemID);

	UStaticMeshComponent* Comp = GetEquipComponent(Slot);
	
	if (Comp)
	{
		Comp->SetStaticMesh(nullptr);
		Comp->SetHiddenInGame(true);
	
		//LocalArmor -= Info.Armor;
	}
}

// Called when the game starts or when spawned
void AUILCharacter::BeginPlay()
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

void AUILCharacter::ToggleQuestListVisibility()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (QuestList)
	{
		QuestList->RemoveFromParent();
		QuestList = nullptr;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		if (QuestListClass)
		{
			QuestList = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
			QuestList->Init(QuestListComp);
			QuestList->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

UStaticMeshComponent* AUILCharacter::GetEquipComponent(EEquipSlot EquipSlot)
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

void AUILCharacter::OpenCloseInventory()
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

// Called every frame
void AUILCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUILCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("InventoryKey", IE_Pressed, this, &ThisClass::OpenCloseInventory);
	}
}

TMap<int32, FInventorySlotInfo> AUILCharacter::SaveInventory() const
{
	TMap<int32, FInventorySlotInfo> Items;
	if (LocalInventory)
	{
		Items = LocalInventory->GetItems();
	}
	return Items;
}

void AUILCharacter::LoadInventory(TMap<int32, FInventorySlotInfo> Inventory)
{
	if (LocalInventory)
	{
		LocalInventory->ClearInventory();

		for (auto Item : Inventory)
		{
			LocalInventory->SetItem(Item.Key,Item.Value);
		}
	}
}

