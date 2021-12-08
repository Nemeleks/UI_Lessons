// Fill out your copyright notice in the Description page of Project Settings.


#include "RButtons.h"

#include "SRadioButtons.h"

void URButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	RButtonsWidget.Reset();
}

TSharedRef<SWidget> URButtons::RebuildWidget()
{
	RButtonsWidget = SNew(SRadioButtons)
	.Style(&WidgetStyle)
	;
	
	return RButtonsWidget.ToSharedRef();
}
