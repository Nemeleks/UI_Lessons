// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidgetForStyle.h"
#include "RButtons.h"
#include "StyleSet.h"

void UTestWidgetForStyle::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RadioButtons)
	{
		RadioButtons->WidgetStyle = FStyleSet::Get().GetWidgetStyle<FMySlateStyleStyle>(FName("WS_RadioButtonsStyle"));
	}
	
}


