// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootBox.generated.h"

UCLASS()
class INVENTORYSYSTEM_API ALootBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALootBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxOverlap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UInventoryManagerComponent* InventoryManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loot")
	class UDataTable* LootTable;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};



