// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySlateStyleWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewSelectedIndex*/);

class UI_LESSONS_API SRadioButtons : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRadioButtons)
		{
		}

	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);

	SLATE_STYLE_ARGUMENT(FMySlateStyleStyle, Style);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnRadioButtonChanged OnRadioButtonChanged;

	void SetRadioButtonsStyle(const FMySlateStyleStyle* InStyle);

protected:

	const FCheckBoxStyle* CheckBoxStyle = nullptr;

	const FTextBlockStyle* TextBlockStyle = nullptr;

private:
	TSharedRef<SWidget> CreateCheckbox(int32 InIndex, FString InText);

	int32 CurrentIndex = 0;

	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex);
};
