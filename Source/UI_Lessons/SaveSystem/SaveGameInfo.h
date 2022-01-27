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
	
	float Health;
	int32 Ammo;
	TMap<int32, FInventorySlotInfo> Items;
};
UCLASS()
class UI_LESSONS_API USaveGameInfo : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float TestFloat;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInfo CharInfo;
};
