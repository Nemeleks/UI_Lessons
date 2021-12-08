// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MainMenuWidgetStyle.h"
#include "StyleSet.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	MenuWidgetStyle = FStyleSet::Get().GetWidgetStyle<FMainMenuStyle>(StyleName);
	
	if (NewGameBtn)
	{
		NewGameBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}

	if (OptionsBtn)
	{
		OptionsBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	
	if (QuitGameBtn)
	{
		QuitGameBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}

	if (NewGameText)
	{
		NewGameText->SetColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ColorAndOpacity);
		NewGameText->SetShadowColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ShadowColorAndOpacity);
		NewGameText->SetFont(MenuWidgetStyle.TextBlockStyle.Font);
	}

	if (OptionsText)
	{
		OptionsText->SetColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ColorAndOpacity);
		OptionsText->SetShadowColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ShadowColorAndOpacity);
		OptionsText->SetFont(MenuWidgetStyle.TextBlockStyle.Font);
	}

	if (QuitGameText)
	{
		QuitGameText->SetColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ColorAndOpacity);
		QuitGameText->SetShadowColorAndOpacity(MenuWidgetStyle.TextBlockStyle.ShadowColorAndOpacity);
		QuitGameText->SetFont(MenuWidgetStyle.TextBlockStyle.Font);
	}
	
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameBtn)
	{
		NewGameBtn->OnClicked.AddDynamic(this, &ThisClass::UMenuWidget::OnNewGameClicked);
	}
	
	if (OptionsBtn)
	{
		OptionsBtn->OnClicked.AddDynamic(this, &ThisClass::UMenuWidget::OnOptionClicked);
	}
	
	if (QuitGameBtn)
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &ThisClass::UMenuWidget::OnQuitGameClicked);
	}
}

void UMenuWidget::OnNewGameClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), NewGameLevelName);
}

void UMenuWidget::OnOptionClicked()
{
}

void UMenuWidget::OnQuitGameClicked()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
}
