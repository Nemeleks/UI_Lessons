// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInfo.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	int32 Ammo;

	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FInventorySlotInfo> Items;
};

USTRUCT(BlueprintType)
struct FEnemyInfo
{

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	int32 Ammo;
	
};

UCLASS()
class SAVESYSTEM_API USaveGameInfo : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float TestFloat;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInfo CharInfo;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FEnemyInfo> EnemyInfo;

	UPROPERTY()
	TArray<uint8> Bytes;

	void CollectData(UWorld* World);
	void ApplyData(UWorld* World);

	
};
