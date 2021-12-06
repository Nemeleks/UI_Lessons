// Fill out your copyright notice in the Description page of Project Settings.


#include "SRadioButtons.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtons::Construct(const FArguments& InArgs)
{

	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			CreateCheckbox(0, TEXT("Option 1"))
		]

		+SVerticalBox::Slot()
		[
			CreateCheckbox(1, TEXT("Option 2"))
		]
		
		+SVerticalBox::Slot()
		[
			CreateCheckbox(2, TEXT("Option 3"))
		]
	];
	
}

TSharedRef<SWidget> SRadioButtons::CreateCheckbox(int32 InIndex, FString InText)
{
	return SNew(SCheckBox)
	.IsChecked_Raw(this, &SRadioButtons::IsChecked, InIndex)
	.OnCheckStateChanged_Raw(this,&SRadioButtons::OnCheckBoxStateChanged, InIndex)
			[
				SNew(STextBlock)
				.Text(FText::FromString(InText))
			];
}

ECheckBoxState SRadioButtons::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SRadioButtons::OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
