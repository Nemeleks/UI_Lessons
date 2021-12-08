// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWidgetForStyle.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API UTestWidgetForStyle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	class URButtons* RadioButtons;
	
};
