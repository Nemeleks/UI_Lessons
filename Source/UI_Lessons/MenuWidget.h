// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenuWidgetStyle.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FMainMenuStyle MenuWidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FName StyleName;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSettings")
	FName NewGameLevelName;

	UPROPERTY(meta = (BindWidget))
	class UButton* NewGameBtn;

	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* OptionsBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameBtn;

	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* NewGameText;

	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* OptionsText;

	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* QuitGameText;

	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnOptionClicked();

	UFUNCTION()
	void OnQuitGameClicked();
};
