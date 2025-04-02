#include "InteractiveButton.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "ButtonWidget.h"
#include "Door.h"

AInteractiveButton::AInteractiveButton()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;
		
	ButtonUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ButtonUI"));
	ButtonUI->SetupAttachment(RootComponent);
	ButtonUI->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	ButtonUI->SetWidgetSpace(EWidgetSpace::World);
	ButtonUI->SetDrawSize(FVector2D(150.f, 20.f));
	ButtonUI->SetPivot(FVector2D(0.5f, 0.5f));

	bIsActivated = false;

	TimeRemaining = TimerDuration;
}

void AInteractiveButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActivated && TimeRemaining > 0.f) 
	{
		TimeRemaining -= DeltaTime;
		if (TimerWidget)
		{
			float ratio = FMath::Clamp(TimeRemaining / TimerDuration, 0.f, 1.f);
			TimerWidget->SetProgress(ratio);
		}
	}
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


	if (ButtonWidgetClass)
	{
		ButtonUI->SetWidgetClass(ButtonWidgetClass);
		ButtonUI->SetVisibility(true);
	}

	TimerWidget = Cast<UButtonWidget>(ButtonUI->GetUserWidgetObject());
	TimerWidget->SetProgress(0.f);
}

void AInteractiveButton::ResetButton()
{
	bIsActivated = false;
	UpdateButtonMaterial();

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{
			Door->EvaluateDoorCondition();
		}
	}
}

void AInteractiveButton::Interact(ACharacter* InteractingCharacter)
{
	bIsActivated = !bIsActivated;
	TimeRemaining = TimerDuration;

	UpdateButtonMaterial();

	if (TimerWidget)
	{
		TimerWidget->SetProgress(1.f);
	}

	if (InteractSound) //To be implemented
	{
		UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());
	}

	for (ADoor* Door : LinkedDoors)
	{
		if (Door)
		{

			Door->EvaluateDoorCondition();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &AInteractiveButton::ResetButton, TimerDuration, false);
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

