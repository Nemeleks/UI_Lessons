// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "MinimapWgt.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API UMinimapWgt : public UWidget
{
	GENERATED_BODY()

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapPoints")
	TArray<FVector2D> MapCoords;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapBoxes")
	TArray<FBox2D> MapBoxCoords;


protected:
	virtual void SynchronizeProperties() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<class SMinimapWidget> MinimapWidget;
};
