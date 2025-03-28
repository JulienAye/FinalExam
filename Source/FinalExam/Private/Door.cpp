// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "InteractiveButton.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	TargetLocation = InitialLocation + FVector(0.f, 0.f, OpenHeight);	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPosition = GetActorLocation();
	FVector DesiredPosition = bIsOpen ? TargetLocation : InitialLocation;

	FVector NewPosition = FMath::VInterpTo(CurrentPosition, DesiredPosition, DeltaTime, DoorSpeed);
	SetActorLocation(NewPosition);
}

void ADoor::RegisterButton(AInteractiveButton* Button)
{
	if (Button && !LinkedButtons.Contains(Button))
	{
		LinkedButtons.Add(Button);
	}
}

void ADoor::EvaluateDoorCondition()
{
	int32 ActivatedButtons = 0;

	for (AInteractiveButton* Button : LinkedButtons)
	{
		if (Button && Button->IsActivated())
		{
			ActivatedButtons++;
		}
	}

	if (ActivatedButtons >= RequiredButtons)
	{
		OpenDoor();
	}
	else {
		CloseDoor();

	}
}

void ADoor::OpenDoor()
{
	bIsOpen = true;
}

void ADoor::CloseDoor()
{
	bIsOpen = false;
}

