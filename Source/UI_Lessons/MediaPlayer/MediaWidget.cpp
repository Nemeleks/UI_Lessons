// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaWidget.h"

#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"

void UMediaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Browse)
	{
		Btn_Browse->OnClicked.AddDynamic(this, &ThisClass::Browse);
	}

	MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Material);
	
}

void UMediaWidget::Browse()
{
	if (MediaPlayer)
	{
		bIsVideo = false;
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
				if (OutFiles[0].Contains("mp4"))
				{
					bIsVideo = true;
				}
			}
			else
			{
				return;
			}
		}
		
		if (bIsVideo)
		{
			UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
			MediaSource->FilePath = Path;
			MediaPlayer->OpenSource(MediaSource);

			const auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn)
			{
				UMediaSoundComponent* Sound = NewObject<UMediaSoundComponent>(PlayerPawn);
				Sound->SetMediaPlayer(MediaPlayer);
				Sound->RegisterComponent();
			}

			MaterialInstanceDynamic->SetTextureParameterValue("Param", nullptr);
			MaterialInstanceDynamic->SetScalarParameterValue("IsVideo", 0);
			OutputImage->SetBrushFromMaterial(MaterialInstanceDynamic);
			
			MediaPlayer->Play();
			auto TrackDimension = MediaPlayer->GetVideoTrackDimensions(INDEX_NONE, INDEX_NONE);
			UE_LOG(LogTemp,Warning,TEXT("Dim = %s"), *TrackDimension.ToString());
			OutputImage->SetBrushSize(FVector2D(TrackDimension.X,TrackDimension.Y));
			
			
		}
		else
		{
			UTexture2D* Tex = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Path);
			if (Tex)
			{
				auto TexSize = Tex->GetImportedSize();
				auto SizeX = Tex->GetSizeX();
				auto SizeY = Tex->GetSizeY();
				UE_LOG(LogTemp,Warning,TEXT("Texture load"));

				MaterialInstanceDynamic->SetTextureParameterValue("Param", Tex);
				MaterialInstanceDynamic->SetScalarParameterValue("IsVideo", 1);
				OutputImage->SetBrushFromMaterial(MaterialInstanceDynamic);
				OutputImage->SetBrushSize(FVector2D(SizeX,SizeY));
			}
			
		}
		
	}
}

int32 UMediaWidget::IsVideo()
{
	if (bIsVideo)
	{
		return 1;
	}
	return 0;
}
