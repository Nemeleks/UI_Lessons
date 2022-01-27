// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"

#include "InventoryManagerComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ALootBox::ALootBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
		SetRootComponent(SceneComponent);
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(RootComponent);

	BoxOverlap = CreateDefaultSubobject<UBoxComponent>("BoxOverlap");
	BoxOverlap->SetupAttachment(MeshComponent);
	BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &ALootBox::OnComponentBeginOverlap);
	BoxOverlap->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap);

	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

// Called when the game starts or when spawned
void ALootBox::BeginPlay()
{
	Super::BeginPlay();

	if (LootTable)
	{
		TArray<FInventorySlotInfo*> Slots;
		LootTable->GetAllRows<FInventorySlotInfo>("", Slots);

		for	(int32 i = 0; i < Slots.Num(); i++)
		{
			InventoryComponent->SetItem(i, *Slots[i]);
		}
	}
	
}

void ALootBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	UE_LOG(LogTemp, Warning, TEXT("BeginOverlap"));
	if (Player == OtherActor)
	{

		InventoryManager->Init(InventoryComponent);
		UE_LOG(LogTemp, Warning, TEXT("Init"));
		
	}
}

void ALootBox::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
	const auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Player == OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("DeInit"));
		InventoryManager->DeInit();
	}
}
// Called every frame
void ALootBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

