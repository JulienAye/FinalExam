// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneCharacter.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "NiagaraComponent.h"
#include "Components/ProgressBar.h"
#include "CloneWidget.h"


// Sets default values
ACloneCharacter::ACloneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ACloneCharacter::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ACloneCharacter::OnOverlapEnd);

	LifeRemaining = LifeDuration;

	CloneWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CloneWidget"));
	CloneWidget->SetupAttachment(RootComponent);
	CloneWidget->SetRelativeLocation(FVector(0.f, 0.f, 250.f));
	CloneWidget->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	CloneWidget->SetWidgetSpace(EWidgetSpace::World);
	CloneWidget->SetDrawSize(FVector2D(150.f, 20.f));
	CloneWidget->SetPivot(FVector2D(0.5f, 0.5f));
	CloneWidget->SetVisibility(true);
	CloneWidget->SetHiddenInGame(false);

	CloneDissolveEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CloneDissolveEffect"));
	CloneDissolveEffect->SetupAttachment(RootComponent);
	CloneDissolveEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ACloneCharacter::BeginPlay()
{	
	Super::BeginPlay();

	UCloneWidget* LifeWidget = Cast<UCloneWidget>(CloneWidget->GetUserWidgetObject());
	if (LifeWidget)
	{
		LifeWidget->SetLifeRatio(LifeRemaining / LifeDuration);
	}

	DissolveMaterial = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);//Take the first material from the mesh (it only have one)

	if (DissolveMaterial)
	{
		DissolveMaterial->SetScalarParameterValue(TEXT("Dissolve"), 0.f);

		
	}

}

// Called every frame
void ACloneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeRemaining -= DeltaTime;

	UCloneWidget* LifeWidget = Cast<UCloneWidget>(CloneWidget->GetUserWidgetObject());
	if (LifeWidget)
	{
		LifeWidget->SetLifeRatio(LifeRemaining / LifeDuration);
	}

	if (LifeRemaining <= 1.5f && !bHasStartedDissolving)
	{
		bHasStartedDissolving = true;
		CloneDissolveEffect->Activate(true);
	}

	if (DissolveMaterial)
	{
		float DissolveRatio = FMath::Clamp(1.f - (LifeRemaining / LifeDuration), 0.f, 1.f);
		DissolveMaterial->SetScalarParameterValue(TEXT("Dissolve"), DissolveRatio);
	}

	if (APlayerController* Player = GetWorld()->GetFirstPlayerController())
	{
		if (Player->PlayerCameraManager)
		{
			FVector CameraLocation = Player->PlayerCameraManager->GetCameraLocation();
			FVector WidgetLocation = CloneWidget->GetComponentLocation();
			FVector Direction = CameraLocation - WidgetLocation;
			FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

			CloneWidget->SetWorldRotation(LookAtRotation);
		}
	}

	if (LifeRemaining <= 0.f)
		DestroyClone();
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