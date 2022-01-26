// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SaveManager.generated.h"

class USaveGame;
class USaveGameInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveAction, const FString&, SlotName);

UCLASS()
class UI_LESSONS_API USaveManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();

	UPROPERTY(BlueprintAssignable)
	FOnSaveAction OnGameSaved;

	UPROPERTY(BlueprintAssignable)
	FOnSaveAction OnGameLoaded;

	UFUNCTION(BlueprintPure)
	bool IsSaveGameExist(const FString& SlotName) const;

	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& SlotName);

protected:

	void OnGameLoadFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

	void OnGameSaveFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UPROPERTY(BlueprintReadWrite)
	USaveGameInfo* CurrentSave;
};
