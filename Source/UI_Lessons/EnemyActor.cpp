// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "SaveActorsSubsystem.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Mesh->SetupAttachment(RootComponent);
}

void AEnemyActor::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	if (Ar.IsSaveGame())
	{
		Ar << Health;
		Ar << Ammo;
	}
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	auto Subsystem  = GetWorld()->GetSubsystem<USaveActorsSubsystem>();
	Subsystem->SaveActor(GetName(), this);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FEnemyInfo AEnemyActor::SaveEnemy()
{
	EnemyInfo.Health = Health;
	EnemyInfo.Ammo = Ammo;

	return EnemyInfo;
}

void AEnemyActor::LoadEnemy(FEnemyInfo Info)
{
	Health = Info.Health;
	Ammo = Info.Ammo;
}

