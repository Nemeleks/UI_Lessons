// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapWgt.h"
#include "SMinimapWidget.h"


void UMinimapWgt::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MinimapWidget.Reset();
}


TSharedRef<SWidget> UMinimapWgt::RebuildWidget()
{
	
	MinimapWidget = SNew(SMinimapWidget)
	.MapBoxes(MapBoxCoords)
	.MapPoints(MapCoords)
	;

	return MinimapWidget.ToSharedRef();
}


