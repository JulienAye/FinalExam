#include "InteractiveButton.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"

AInteractiveButton::AInteractiveButton()
{
	PrimaryActorTick.bCanEverTick = false;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;
}

// Called when the game starts or when spawned
void AInteractiveButton::BeginPlay()
{
	Super::BeginPlay();

}

void AInteractiveButton::Interact(ACharacter* InteractingCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Bouton activé par : %s"), *InteractingCharacter->GetName());
}

