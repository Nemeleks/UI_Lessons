// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadMenu.h"

#include "SaveActorsSubsystem.h"
#include "SaveGameInfo.h"
#include "SaveGameInstance.h"
#include "SaveManager.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI_Lessons/EnemyActor.h"
#include "UI_Lessons/UILCharacter.h"

void USaveLoadMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (SaveBtn)
	{
		SaveBtn->OnClicked.AddDynamic(this, &ThisClass::USaveLoadMenu::SaveFunc);
	}
	if (LoadBtn)
	{
		LoadBtn->OnClicked.AddDynamic(this, &ThisClass::LoadFunc);
	}
}

void USaveLoadMenu::SaveFunc()
{
	auto GameInstance = Cast<USaveGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto SaveManager = GameInstance->SaveManager;
	auto CurrentSave = SaveManager->GetCurrentSave();
	auto Character = Cast<AUILCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	auto Subsystem = GetWorld()->GetSubsystem<USaveActorsSubsystem>();
	CurrentSave->CharInfo = Character->SaveCharacter();
	
	auto Enemies = Subsystem->GetEnemies();
	for (auto Enemy : Enemies)
	{
		CurrentSave->EnemyInfo.Add(Enemy.Key, Enemy.Value->SaveEnemy());
	}
	
	SaveManager->SaveGame(SlotName);
}

void USaveLoadMenu::LoadFunc()
{
	auto GameInstance = Cast<USaveGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto SaveManager = GameInstance->SaveManager;
	auto CurrentSave = SaveManager->GetCurrentSave();
	auto Character = Cast<AUILCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	auto Subsystem = GetWorld()->GetSubsystem<USaveActorsSubsystem>();
	SaveManager->LoadGame(SlotName);
	Character->LoadCharacter(CurrentSave->CharInfo);

	auto Enemies = Subsystem->GetEnemies();
	for (auto Enemy : Enemies)
	{
		for (auto ToLoad : CurrentSave->EnemyInfo)
		{
			if (Enemy.Key == ToLoad.Key)
			{
				if (auto En = Cast<AEnemyActor>(Enemy.Value))
				{
					En->LoadEnemy(ToLoad.Value);
				}
			}
		}
		
	}
}
