// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractableInterface.h"
#include "Engine/World.h"
#include "CloneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 64.f)); // ajustable selon ton mesh
	Camera->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHp = MaxHp;

}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr) //Adding movement input to controller
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//Get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movement 
		AddMovementInput(ForwardDirection, MoveAxisVector.Y);
		AddMovementInput(RightDirection, MoveAxisVector.X);
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>() * valueAim;

	if (Controller != nullptr) //Adding yaw and pitch axis to the camera
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMainCharacter::Crouch(const FInputActionValue& Value)
{
	//To be implemented
}

void AMainCharacter::Sprint(const FInputActionValue& Value)
{
	bSprint = Value.Get<bool>();

	if (bSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}

void AMainCharacter::UseInteract(const FInputActionValue& Value)
{
	if (!Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("player camera is null"));
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	//Get camera location and rotation
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//Raycast
	FVector StartRay = Camera->GetComponentLocation();
	FVector EndRay = StartRay + (Camera->GetComponentRotation().Vector() * 500.f);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartRay, EndRay, ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), StartRay, EndRay, FColor::Red, false, 1.f, 0, 2.f);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor(); //Get the actor hit  
		if (HitActor && HitActor->Implements<UInteractableInterface>()) //Check if the actor implements the InteractableInterface
		{
			IInteractableInterface* Interactable = Cast<IInteractableInterface>(HitActor);
			if (Interactable) //If the actor implements the interface, call the Interact function
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Interacted with something"));
				}
				Interactable->Interact(this);
			}
		}
	}

	for (ACloneCharacter* Clone : ActiveClones)
	{
		if (Clone && IsValid(Clone)) //Check if the clone is not being destroyed
		{
			Clone->CloneInteract();
		}
	}
}

void AMainCharacter::SpawnClone(const FInputActionValue& Value)
{
	if (AvailableClones <= 0) 
		return;

	if (CloneClass)
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50.f;
		FRotator SpawnRotation = GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ACloneCharacter* Clone = GetWorld()->SpawnActor<ACloneCharacter>(CloneClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (Clone)
		{
			AvailableClones--;
			ActiveClones.Add(Clone);//I add the clone to my ActiveClones array, will be easier in the future to manage their interactions or delete them
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMainCharacter::Sprint);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMainCharacter::UseInteract);
		EnhancedInputComponent->BindAction(SpawnCloneAction, ETriggerEvent::Triggered, this, &AMainCharacter::SpawnClone);
	}
}

void AMainCharacter::NotifyCloneDestruction()
{
	AvailableClones++;
}
