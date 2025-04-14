// Fill out your copyright notice in the Description page of Project Settings.


#include "BobbyActor.h"
#include "BobbyAnimInstance.h"

// Sets default values
ABobbyActor::ABobbyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BobbyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BobbyMesh"));
	RootComponent = BobbyMesh;


}

// Called when the game starts or when spawned
void ABobbyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABobbyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABobbyActor::SayHello()
{
	if (UBobbyAnimInstance* BobbyAnim = Cast<UBobbyAnimInstance>(BobbyMesh->GetAnimInstance()))
	{
		BobbyAnim->bIsSayingHello = true;
		GetWorldTimerManager().ClearTimer(HelloResetHandle);
		GetWorldTimerManager().SetTimer(HelloResetHandle, [BobbyAnim](){BobbyAnim->bIsSayingHello = false;}, 2.0, false);
	}
}

void ABobbyActor::Move()
{
	if (UBobbyAnimInstance* BobbyAnim = Cast<UBobbyAnimInstance>(BobbyMesh->GetAnimInstance()))
	{
		//BobbyAnim->bIsMoving = true;
	}
}

void ABobbyActor::MoveToLocation(const FVector& Location)
{
	Move();

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = Location;

	const float Duration = 1.f;

	float ElapsedTime = 0.f;
	const float Step = 0.02f;

	FTimerHandle MoveHandle;

	GetWorldTimerManager().SetTimer(MoveHandle, [this, StartLocation, EndLocation, Duration, Step, ElapsedTime]() mutable { //mutable to modify ElapsedTime
		ElapsedTime += Step;
		float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f); //So Alpha max = 1
		FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
		SetActorLocation(NewLocation);

		if (Alpha >= 1.f)
		{
			if (UBobbyAnimInstance* BobbyAnim = Cast<UBobbyAnimInstance>(BobbyMesh->GetAnimInstance()))
			{
				BobbyAnim->bIsMoving = false;
			}
			//GetWorldTimerManager().ClearTimer(MoveHandle);
		}
		}, Step, true);
}

