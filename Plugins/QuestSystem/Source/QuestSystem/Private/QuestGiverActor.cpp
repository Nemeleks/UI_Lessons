// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiverActor.h"

#include "QuestDialog.h"
#include "QuestListComponent.h"


// Sets default values
AQuestGiverActor::AQuestGiverActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshChar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharMesh"));
	StaticMeshChar->SetupAttachment(RootComponent);

	StaticMeshAvailableQuest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshAvailableQuest"));
	StaticMeshAvailableQuest->SetupAttachment(StaticMeshChar);
	
	StaticMeshTakenQuest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshTakenQuest"));
	StaticMeshTakenQuest->SetupAttachment(StaticMeshChar);
    	
	StaticMeshCompletedQuest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComplitedQuest"));
	StaticMeshCompletedQuest->SetupAttachment(StaticMeshChar);
	
}

// Called when the game starts or when spawned
void AQuestGiverActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetAttachedActors(AttachedActors);
	for (AActor* Actor : AttachedActors)
	{
		if (AQuestActor* Quest = Cast<AQuestActor>(Actor))
		{
			if (Quest)
			{
				Quest->OnQuestStatusChanged.AddDynamic(this, &ThisClass::AQuestGiverActor::HasAvailableQuests);
			}
		}
	}

	if (StaticMeshAvailableQuest)
	{
		HasAvailableQuests();
	}
	
	
}

void AQuestGiverActor::SinusoidMovement(float DeltaSeconds)
{
		float CurrentZ = StaticMeshAvailableQuest->GetRelativeLocation().Z;
		TimeCount+= DeltaSeconds * Speed;
		Theta = FMath::Sin(TimeCount);
		float NewZ = Theta * Amplitude + CurrentZ;
		StaticMeshAvailableQuest->SetRelativeLocation(FVector(0.f,0.f, NewZ));
}

void AQuestGiverActor::HasAvailableQuests()
{
	for (AActor* Actor : AttachedActors)
	{
		if (AQuestActor* Quest = Cast<AQuestActor>(Actor))
		{
			if (Quest && Quest->bIsTaken && !Quest->bIsCompleted)
			{
				bHasAvailableQuest = false;
				StaticMeshAvailableQuest->SetVisibility(false);
				StaticMeshCompletedQuest->SetVisibility(false);
				StaticMeshTakenQuest->SetVisibility(true);
				return;
			}
			if (Quest && Quest->bIsCompleted)
			{
				bHasAvailableQuest = false;
				StaticMeshAvailableQuest->SetVisibility(false);
				StaticMeshCompletedQuest->SetVisibility(true);
				StaticMeshTakenQuest->SetVisibility(false);
				return;
			}
			if (Quest && Quest->IsAvailable())
			{
				bHasAvailableQuest = true;
				StaticMeshAvailableQuest->SetVisibility(true);
				StaticMeshCompletedQuest->SetVisibility(false);
				StaticMeshTakenQuest->SetVisibility(false);
				return;
			}
			
			bHasAvailableQuest = false;
			StaticMeshAvailableQuest->SetVisibility(false);
			StaticMeshCompletedQuest->SetVisibility(false);
			StaticMeshTakenQuest->SetVisibility(false);
			
		}
	}

}

// Called every frame
void AQuestGiverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bHasAvailableQuest)
	{
		SinusoidMovement(DeltaTime);
	}
	
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
						return;
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

void AQuestGiverActor::SetTickAndVisibility(bool HasAvailableQuest)
{
	if (StaticMeshAvailableQuest)
	{
		StaticMeshAvailableQuest->SetVisibility(HasAvailableQuest);
	}
	bHasAvailableQuest = HasAvailableQuest;
}