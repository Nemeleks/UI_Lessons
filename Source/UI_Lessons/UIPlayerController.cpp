// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPlayerController.h"

AUIPlayerController::AUIPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bEnableClickEvents = true;
}

void AUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AUIPlayerController::OnLeftMouseButtonUp);
	}
}

void AUIPlayerController::OnLeftMouseButtonUp()
{
	if (OnMouseButtonUp.IsBound())
	{
		OnMouseButtonUp.Broadcast();
	}
}
