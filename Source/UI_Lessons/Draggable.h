// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Draggable.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSONS_API UDraggable : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString TankName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TankText;

	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
	void OnTestDragCancelled(UDragDropOperation* Operation);
};
