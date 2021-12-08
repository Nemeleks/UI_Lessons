// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySlateStyleWidgetStyle.h"
#include "Components/Widget.h"
#include "RButtons.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API URButtons : public UWidget
{
	GENERATED_BODY()

public:
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FMySlateStyleStyle WidgetStyle;
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	

private:
	TSharedPtr<class SRadioButtons> RButtonsWidget;
	
};
