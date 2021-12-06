// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class UI_LESSONS_API SMinimapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinimapWidget)
	{
	}

	SLATE_ARGUMENT(TArray<FVector2D>, MapPoints);
	SLATE_ARGUMENT(TArray<FBox2D>, MapBoxes);
	
	SLATE_END_ARGS()
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

protected:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	FVector2D PlayerPosition;

public:
	
	void SetMapPoints(TArray<FVector2D> NewPoints) { MapPoints = NewPoints;}
	void SetMapBoxes(TArray<FBox2D> NewBoxes) {MapBoxes = NewBoxes;}

private:
	TArray<FVector2D>  MapPoints;
	TArray<FBox2D> MapBoxes;

};
