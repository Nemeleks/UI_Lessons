// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWgt.h"
#include "UIPlayerController.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UActorSpawnerWgt::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SpawnActorText)
	{
		SpawnActorText->SetText(FText::FromString(SpawnActorName));
	}
}

void UActorSpawnerWgt::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerController = Cast<AUIPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->OnMouseButtonUp.AddUObject(this, &UActorSpawnerWgt::OnMouseButtonUp);
	}
	
	
}

FReply UActorSpawnerWgt::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass);
	}
	return FReply::Handled();
}

void UActorSpawnerWgt::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnActorText->IsHovered())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hovered"));
	}

	if (SpawnActor && PlayerController)
	{
		SpawnActor->SetActorEnableCollision(false);
		FVector WorldMouseLocation;
		FVector WorldMouseDirection;

		PlayerController->DeprojectMousePositionToWorld(WorldMouseLocation, WorldMouseDirection);

		FHitResult HitResult;
		float TraceDistance = 100000.f;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());


		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			WorldMouseLocation,
			WorldMouseLocation+WorldMouseDirection*TraceDistance,
			ECollisionChannel::ECC_WorldStatic,
			Params
		
		);

		if (HitResult.bBlockingHit)
		{
			SpawnActor->SetActorLocation(HitResult.Location, false);
		}
	}
}

void UActorSpawnerWgt::OnMouseButtonUp()
{
	if (SpawnActor)
	{
		SpawnActor->SetActorEnableCollision(true);
		SpawnActor = nullptr;
	}
}
