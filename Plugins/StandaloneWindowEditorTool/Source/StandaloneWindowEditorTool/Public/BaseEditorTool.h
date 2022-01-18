// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseEditorTool.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class STANDALONEWINDOWEDITORTOOL_API UBaseEditorTool : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Hidden")
	FText HelpText;
};
