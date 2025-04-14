// Fill out your copyright notice in the Description page of Project Settings.


#include "CloneBonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include"MainCharacter.h"
#include "TutorielManager.h"

// Sets default values
ACloneBonus::ACloneBonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->InitSphereRadius(10.f);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACloneBonus::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACloneBonus::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACloneBonus::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (OtherActor && OtherActor != this)
    {
        AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
        if (Player)
        {
            if (!bHasTriggeredTutorialEvent && TutorielManager)
            {
                TutorielManager->TriggerEvent();
                bHasTriggeredTutorialEvent = true;
            }
            Player->NotifyCloneDestruction();
            Destroy();
        }
    }
}

// Called every frame
void ACloneBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

