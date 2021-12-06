// Fill out your copyright notice in the Description page of Project Settings.


#include "SMinimapWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMinimapWidget::Construct(const FArguments& InArgs)
{
	MapPoints = InArgs._MapPoints;
	MapBoxes = InArgs._MapBoxes;
}

int32 SMinimapWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		MapPoints);

	++LayerId;

	for (int32 i = 0; i < MapBoxes.Num(); ++i)
	{
		TArray<FVector2D> Box;
		Box.Add(MapBoxes[i].Min);
		Box.Add(MapBoxes[i].Max);
		
		FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		Box);
	}


	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}




END_SLATE_FUNCTION_BUILD_OPTIMIZATION



