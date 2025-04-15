#include "TriggerDialogueBox.h"
#include "Components/BoxComponent.h"
#include "TutorielManager.h"
#include "MainCharacter.h"

ATriggerDialogueBox::ATriggerDialogueBox()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetBoxExtent(FVector(100.f));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerDialogueBox::OnOverlapBegin);
}

void ATriggerDialogueBox::BeginPlay()
{
	Super::BeginPlay();
}

void ATriggerDialogueBox::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{

	if (AMainCharacter* Player = Cast<AMainCharacter>(OtherActor))
	{
		if (!bHasTriggeredTutorialEvent && TutorielManager)
		{
			TutorielManager->TriggerEvent();
			bHasTriggeredTutorialEvent = true;
		}
	}
}
