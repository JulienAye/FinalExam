#include "InteractiveButton.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"

AInteractiveButton::AInteractiveButton()
{
	PrimaryActorTick.bCanEverTick = false;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;

	bIsActivated = false;
}

// Called when the game starts or when spawned
void AInteractiveButton::BeginPlay()
{
	Super::BeginPlay();

	UpdateButtonMaterial();

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{
			Door->RegisterButton(this); //Mandatory to synchronize all buttons with the door
		}
	}
}

void AInteractiveButton::Interact(ACharacter* InteractingCharacter)
{
	bIsActivated = !bIsActivated;

	UpdateButtonMaterial();

	if (InteractSound) //To be implemented
	{
		UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());
	}

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{

			Door->EvaluateDoorCondition();
			//if (Door->bIsOpen)
			//{
			//	Door->CloseDoor();
			//}
			//else
			//{
			//	Door->OpenDoor();
			//}
		}
	}
}

void AInteractiveButton::UpdateButtonMaterial()
{
	if (bIsActivated)
	{
		ButtonMesh->SetMaterial(0, ActivatedMaterial);
	}
	else
	{
		ButtonMesh->SetMaterial(0, DeactivatedMaterial);
	}
}

