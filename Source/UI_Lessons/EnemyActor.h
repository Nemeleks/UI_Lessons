// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "InteractableObject.h"
#include "GameFramework/Actor.h"
#include "SaveGameInfo.h"
#include "EnemyActor.generated.h"

UCLASS()
class UI_LESSONS_API AEnemyActor : public AActor, public IDamageable, public IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

	virtual void Serialize(FArchive& Ar) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Params To Save")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Params To Save")
	int32 Ammo = 50;

	FEnemyInfo EnemyInfo;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FEnemyInfo SaveEnemy () override;

	void LoadEnemy(FEnemyInfo Info);

	UFUNCTION(BlueprintCallable)
	FString GetEnemyName() const {return GetName();}
};
