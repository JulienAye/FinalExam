// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneCharacter.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "InteractableInterface.h"

// Sets default values
ACloneCharacter::ACloneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ACloneCharacter::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ACloneCharacter::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACloneCharacter::BeginPlay()
{	
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACloneCharacter::DestroyClone, 5.f, false, 5.f);
}

// Called every frame
void ACloneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACloneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACloneCharacter::CloneInteract()
{
	if (ActorsToInteract.Num() > 0)
	{
		AActor* Target = ActorsToInteract[0];
		if (Target && Target->Implements<UInteractableInterface>())
		{
			IInteractableInterface* Interactable = Cast<IInteractableInterface>(Target);
			if (Interactable)
			{
				Interactable->Interact(this);
			}
		}
	}
}

void ACloneCharacter::DestroyClone()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AMainCharacter* Player = Cast<AMainCharacter>(OwnerCharacter);
		if (Player)
		{
			Player->NotifyCloneDestruction(); //Notify the player so he can spawn another clone
		}
	}

	//Visual effect to be implemented
	Destroy();
}

void ACloneCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UInteractableInterface>())
	{
		ActorsToInteract.AddUnique(OtherActor);
	}
}	

void ACloneCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActorsToInteract.Remove(OtherActor);
}