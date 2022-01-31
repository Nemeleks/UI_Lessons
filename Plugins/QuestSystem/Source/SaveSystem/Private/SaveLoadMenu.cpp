// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadMenu.h"

#include "SaveGameInstance.h"
#include "SaveManager.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


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
	
	SaveManager->SaveGame(SlotName);
}

void USaveLoadMenu::LoadFunc()
{
	auto GameInstance = Cast<USaveGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto SaveManager = GameInstance->SaveManager;
	
	SaveManager->LoadGame(SlotName);

}
