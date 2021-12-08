// Fill out your copyright notice in the Description page of Project Settings.


#include "MySlateStyleWidgetStyle.h"


FMySlateStyleStyle::FMySlateStyleStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox");
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
}

FMySlateStyleStyle::~FMySlateStyleStyle()
{
}

const FName FMySlateStyleStyle::TypeName(TEXT("FMySlateStyleStyle"));

const FMySlateStyleStyle& FMySlateStyleStyle::GetDefault()
{
	static FMySlateStyleStyle Default;
	return Default;
}

void FMySlateStyleStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}
