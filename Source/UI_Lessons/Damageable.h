// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSystem/SaveGameInfo.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UI_LESSONS_API IDamageable
{
	GENERATED_BODY()
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FEnemyInfo SaveEnemy() = 0;
};
