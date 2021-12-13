// Fill out your copyright notice in the Description page of Project Settings.


#include "Draggable.h"

#include "TestDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UDraggable::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TankText)
	{
		TankText->SetText(FText::FromString(TankName));
	}
}

FReply UDraggable::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	
	return FReply::Handled();
}

void UDraggable::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UTestDragDropOperation::StaticClass());
	UTestDragDropOperation* TestDDOperation = Cast<UTestDragDropOperation>(OutOperation);

	if (TestDDOperation)
	{
		TestDDOperation->DefaultDragVisual = this;

		SetColorAndOpacity(FLinearColor(1.f,1.f,1.f, 0.7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		TestDDOperation->OnDragCancelled.AddDynamic(this, &ThisClass::UDraggable::OnTestDragCancelled);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDraggable::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	
	UVerticalBox* VerticalBox = Cast<UVerticalBox>(GetParent());
	UTestDragDropOperation* TestDDOperation = Cast<UTestDragDropOperation>(InOperation);

	if (VerticalBox && TestDDOperation && TestDDOperation->DefaultDragVisual && this != TestDDOperation->DefaultDragVisual)
	{
		const int32 OverIndex = VerticalBox->GetChildIndex(TestDDOperation->DefaultDragVisual);

		if (OverIndex >= 0)
		{
			VerticalBox->RemoveChildAt(OverIndex);

			const TArray<UWidget*> Children =  VerticalBox->GetAllChildren();
			VerticalBox->ClearChildren();

			for (int32 i = 0; i < Children.Num(); i++)
			{
				if (Children[i] == this)
				{
					VerticalBox->AddChildToVerticalBox(TestDDOperation->DefaultDragVisual)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				}
				
				VerticalBox->AddChildToVerticalBox(Children[i])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			}
			return true;
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	
}

bool UDraggable::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		OnTestDragCancelled(InOperation);
		return true;
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

}

void UDraggable::OnTestDragCancelled(UDragDropOperation* Operation)
{
	UDraggable* DraggableItem = Cast<UDraggable>(Operation->DefaultDragVisual);
	if (DraggableItem)
	{
		SetColorAndOpacity(FLinearColor(1.f,1.f,1.f, 1.f));
		SetVisibility(ESlateVisibility::Visible);
	}
}
