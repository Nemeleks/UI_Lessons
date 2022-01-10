// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestActor.h"

#include "Objective.h"


// Sets default values
AQuestActor::AQuestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestActor::BeginPlay()
{
	Super::BeginPlay();

	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		TakeQuest(ParentActor);
	}
	
}

// Called every frame
void AQuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestActor::TakeQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];
		if (Objective == nullptr)
		{
			continue;
		}

		Objective->ActivateObjective(Character);
		Objective->bCanBeCompleted = i == 0 || !bKeepObjectivesOrder;
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
	}
	bIsTaken = true;
}

void AQuestActor::OnObjectiveCompleted(UObjective* Objective)
{
	if (bKeepObjectivesOrder)
	{
		int32 Index;
		if (Objectives.Find(Objective, Index) && Objectives.IsValidIndex(Index+1))
		{
			Objectives[Index+1]->bCanBeCompleted = true;
		}
	}
}


void AQuestActor::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuestActor::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

void AQuestActor::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

void AQuestActor::AddCollectionObjective()
{
	Objectives.Add(NewObject<UCollectionObjective>(this));
}

