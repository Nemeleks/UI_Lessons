// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorSpawnerWgt.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UI_LESSONS_API UActorSpawnerWgt : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* SpawnActorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SpawnActorName;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnActorClass;

	UPROPERTY()
	AActor* SpawnActor;

	UPROPERTY()
	class AUIPlayerController* PlayerController;

	void OnMouseButtonUp();
};

