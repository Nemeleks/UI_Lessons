// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "MainMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct UI_LESSONS_API FMainMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FMainMenuStyle();
	virtual ~FMainMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMainMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FTextBlockStyle TextBlockStyle;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UMainMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FMainMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
