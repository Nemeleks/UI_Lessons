// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestList.h"
#include "EquipInterface.h"
#include "InventoryComponent.h"
#include "GameFramework/Character.h"
#include "SaveGameInfo.h"
#include "UILCharacter.generated.h"

UCLASS()
class UI_LESSONS_API AUILCharacter : public ACharacter, public IEquipInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUILCharacter();

	void SetClassInventory(UDataTable* InventoryData) {StartInventory = InventoryData;}

	virtual void EquipItem_Implementation(EEquipSlot Slot, FName ItemID) override;
	
	virtual void UnEquipItem_Implementation(EEquipSlot Slot, FName ItemID) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleQuestListVisibility();

	UPROPERTY()
	UQuestList* QuestList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestList> QuestListClass;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSystem")
	class UQuestListComponent* QuestListComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "InventoryCharacter")
	class UInventoryComponent* LocalInventory;

	UPROPERTY(VisibleDefaultsOnly, Category = "InventoryCharacter")
	class UEquipInventoryComponent* EquipInventory;
	
	UPROPERTY(EditDefaultsOnly, Category = "InventoryCharacter")
	class UInventoryManagerComponent* LocalInventoryManager;

	UPROPERTY(EditDefaultsOnly, Category = "InventoryCharacter")
	UDataTable* StartInventory;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Health = 100.f;

	UStaticMeshComponent* GetEquipComponent(EEquipSlot EquipSlot);

	void OpenCloseInventory();

	FCharacterInfo CharacterInfo;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Serialize(FArchive& Ar) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	TMap<int32, FInventorySlotInfo> SaveInventory() const;

	UFUNCTION(BlueprintCallable)
	FCharacterInfo SaveCharacter();

	UFUNCTION(BlueprintCallable)
	void LoadCharacter(FCharacterInfo LoadInfo);

	UFUNCTION(BlueprintCallable)
	void LoadInventory(TMap<int32, FInventorySlotInfo> Inventory);

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth) {Health = NewHealth;}

	UFUNCTION(BlueprintCallable)
	float GetHealth() const {return Health;}
};
