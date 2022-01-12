// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "QuestGiverActor.generated.h"

class UQuestDialog;

UCLASS()
class QUESTSYSTEM_API AQuestGiverActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestGiverActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "QuestSystem")
	TSubclassOf<UQuestDialog> QuestDialogClass;

	UFUNCTION(BlueprintCallable)
	void SinusoidMovement(float DeltaSeconds, float Amplitude, float Speed, UStaticMeshComponent* StaticMesh);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* InteractInstigator) override;

private:
	float TimeCount;
	float Theta;
};
