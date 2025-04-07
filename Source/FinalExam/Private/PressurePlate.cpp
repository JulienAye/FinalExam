// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CloneCharacter.h"
#include "MainCharacter.h"
#include "Door.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(50.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(RootComponent);

	bIsActivated = false;

}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{
			Door->RegisterPressurePlate(this); //Mandatory to synchronize all buttons with the door
		}
	}
	
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACloneCharacter>(OtherActor) || Cast<AMainCharacter>(OtherActor))
	{
		bIsActivated = true;
		PlateMesh->SetMaterial(0, ActiveMaterial);
		for (ADoor* Door : LinkedDoors)
		{
			if (Door && !Door->bIsOpen)
			{
				
				Door->EvaluateDoorCondition();
			}
		}
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACloneCharacter>(OtherActor) || Cast<AMainCharacter>(OtherActor))
	{
		bIsActivated = false;
		PlateMesh->SetMaterial(0, DefaultMaterial);

		for (ADoor* Door : LinkedDoors)
		{
			if (Door && Door->bIsOpen)
			{
				Door->EvaluateDoorCondition();
				
			}
		}
	}
}

// Called every frame
//void APressurePlate::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

