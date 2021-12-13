// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUIPlayerController(const FObjectInitializer& ObjectInitializer);

	FSimpleMulticastDelegate OnMouseButtonUp;

protected:
	virtual void SetupInputComponent() override;
	void OnLeftMouseButtonUp();
};
