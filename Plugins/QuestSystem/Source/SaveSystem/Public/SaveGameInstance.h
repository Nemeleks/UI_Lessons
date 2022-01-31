// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameInstance.generated.h"

class USaveManager;

UCLASS()
class SAVESYSTEM_API USaveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly)
	USaveManager* SaveManager;
};
