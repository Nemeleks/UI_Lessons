// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UI_Lessons/Damageable.h"
#include "SaveActorsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API USaveActorsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	TMap<FString, IDamageable*> Enemies;

public:
	void AddEnemy(FString Name, IDamageable* EnemyPtr){Enemies.Add(Name, EnemyPtr);}
	TMap<FString, IDamageable*> GetEnemies() const {return Enemies;}
	
};
