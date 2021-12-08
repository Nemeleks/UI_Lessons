// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidgetStyle.h"


FMainMenuStyle::FMainMenuStyle()
{
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
}

FMainMenuStyle::~FMainMenuStyle()
{
}

const FName FMainMenuStyle::TypeName(TEXT("FMainMenuStyle"));

const FMainMenuStyle& FMainMenuStyle::GetDefault()
{
	static FMainMenuStyle Default;
	return Default;
}

void FMainMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}
