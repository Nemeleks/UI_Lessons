// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoPlane.h"

#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "Kismet/KismetRenderingLibrary.h"


// Sets default values
AVideoPlane::AVideoPlane()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVideoPlane::BeginPlay()
{
	Super::BeginPlay();

	if (MediaPlayer)
	{
		FString Path;

		IDesktopPlatform* Platform = FDesktopPlatformModule::Get();

		if (Platform)
		{
			auto* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
			const FString FileTypes = "All Files (*.PNG, *.JPG, *.MP4)|*.PNG;*.JPG;*.MP4|"
									"Video Files (*.MP4)|*.MP4|"
									"Image Files (*.PNG, *.JPG)|*.PNG;*.JPG";

			TArray<FString> OutFiles;

			Platform->OpenFileDialog(ParentHandle, "Choose media: ", "", "", FileTypes, 0, OutFiles);
			if (OutFiles.Num() > 0)
			{
				Path = OutFiles[0];
			}
		}

		//UTexture2D* Tex = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Path);
		
		UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = Path;
		MediaPlayer->OpenSource(MediaSource);

		UMediaSoundComponent* Sound = NewObject<UMediaSoundComponent>(this);
		Sound->SetMediaPlayer(MediaPlayer);
		Sound->RegisterComponent();
	}
	
}

// Called every frame
void AVideoPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

