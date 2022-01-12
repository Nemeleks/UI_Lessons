// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiverActor.h"

#include "QuestDialog.h"
#include "QuestListComponent.h"


// Sets default values
AQuestGiverActor::AQuestGiverActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestGiverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQuestGiverActor::SinusoidMovement(float DeltaSeconds, float Amplitude, float Speed, UStaticMeshComponent* StaticMesh)
{
	float CurrentZ = StaticMesh->GetRelativeLocation().Z;
	TimeCount+= DeltaSeconds * Speed;
	Theta = FMath::Sin(TimeCount);
	float NewZ = Theta * Amplitude + CurrentZ;
	StaticMesh->SetRelativeLocation(FVector(0.f,0.f, NewZ));
}

// Called every frame
void AQuestGiverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestGiverActor::Interact_Implementation(AActor* InteractInstigator)
{
	Super::Interact_Implementation(InteractInstigator);

	if (InteractInstigator)
	{
		UActorComponent* ActorQuestListComp = InteractInstigator->GetComponentByClass(UQuestListComponent::StaticClass());

		if (ActorQuestListComp)
		{
			auto* ActorQuestList = Cast<UQuestListComponent>(ActorQuestListComp);

			TArray<AActor*> AttachedActors;
			GetAttachedActors(AttachedActors);
			bool bHasQuestsAvailable = false;

			for (AActor* Actor : AttachedActors)
			{
				if (AQuestActor* Quest = Cast<AQuestActor>(Actor))
				{
					if (Quest->bIsTaken || Quest->PreviousQuest && !Quest->PreviousQuest->bIsCompleted)
					{
						continue;
					}

					if (QuestDialogClass)
					{
						UQuestDialog* QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
						QuestDialog->Init(Quest);
						QuestDialog->OnQuestAccepted.BindUObject(ActorQuestList, &UQuestListComponent::AddQuest, Quest);
						QuestDialog->OnQuestQuited.BindLambda([this, InteractInstigator]()
						{
							NotifyInteractionFinished(this, InteractInstigator);	
						}
						);
						QuestDialog->AddToViewport();
					}

					bHasQuestsAvailable = true;
				}

			}

			if (!bHasQuestsAvailable)
			{
				NotifyInteractionFinished(this, InteractInstigator);
			}
		}
	}
}

