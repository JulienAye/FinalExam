// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleWall.h"
#include "InteractiveButton.h"
#include "PressurePlate.h"

// Sets default values
AObstacleWall::AObstacleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = WallMesh;

}

// Called when the game starts or when spawned
void AObstacleWall::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
}

bool AObstacleWall::AreAllConditionsMet() const
{
	for (AInteractiveButton* Button : Buttons)
	{
		if (!Button || !Button->IsActivated())
			return false;
	}

	for (APressurePlate* Plate : PressurePlates)
	{
		if (!Plate || !Plate->bIsActivated)
			return false;
	}

	return true;
}

void AObstacleWall::RegisterPressurePlate(APressurePlate* PressurePlate)
{
	if (PressurePlate && !PressurePlates.Contains(PressurePlate))
	{
		PressurePlates.Add(PressurePlate);
	}
}

void AObstacleWall::RegisterButton(AInteractiveButton* Button)
{
	if (Button && !Buttons.Contains(Button))
	{
		Buttons.Add(Button);
	}
}

void AObstacleWall::EvaluateConditions()
{
	if (!bIsLowered && AreAllConditionsMet())
	{
		FVector NewLocation = InitialLocation;
		NewLocation.Z += LoweredZOffset;
		SetActorLocation(NewLocation);

		bIsLowered = true;
	}
	else if (bIsLowered && !AreAllConditionsMet())
	{
		SetActorLocation(InitialLocation);
		bIsLowered = false;
	}
}

// Called every frame
void AObstacleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

