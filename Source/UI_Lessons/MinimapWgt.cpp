// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapWgt.h"
#include "SMinimapWidget.h"


void UMinimapWgt::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MinimapWidget.Reset();
}

void UMinimapWgt::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	
}

TSharedRef<SWidget> UMinimapWgt::RebuildWidget()
{
	//return Super::RebuildWidget();
	MinimapWidget = SNew(SMinimapWidget);
	MinimapWidget->SetMapPoints(MapCoords);
	MinimapWidget->SetMapBoxes(MapBoxCoords);

	return MinimapWidget.ToSharedRef();
}


