#include "InteractiveButton.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Door.h"

AInteractiveButton::AInteractiveButton()
{
	PrimaryActorTick.bCanEverTick = false;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;

	bIsActivated = true;
}

// Called when the game starts or when spawned
void AInteractiveButton::BeginPlay()
{
	Super::BeginPlay();

}

void AInteractiveButton::Interact(ACharacter* InteractingCharacter)
{
	bIsActivated = !bIsActivated;

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{
			if (Door->bIsOpen)
			{
				Door->CloseDoor();
			}
			else
			{
				Door->OpenDoor();
			}
		}
	}
}

