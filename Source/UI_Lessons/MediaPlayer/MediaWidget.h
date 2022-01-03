// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API UMediaWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Btn_Browse;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* OutputImage;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMediaPlayer* MediaPlayer;

private:

	UFUNCTION(BlueprintCallable)
	void Browse();
	
	UFUNCTION(BlueprintCallable)
	int32 IsVideo();

	bool bIsVideo = false;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;
};
