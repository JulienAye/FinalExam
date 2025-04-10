// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorielManager.h"
#include "TutorialDialogue.h"
#include "MainCharacter.h"
#include "PlayerHUDWidget.h"

// Sets default values
ATutorielManager::ATutorielManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ATutorielManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &ATutorielManager::InitializeTutorial, 0.2f, false);	
}

void ATutorielManager::InitializeTutorial() //To be called when the player is ready, otherwise is null
{
	if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (AMainCharacter* Player = Cast<AMainCharacter>(PC->GetPawn()))
		{
			if (Player->PlayerHUD)
			{
				TutorialWidget = Player->PlayerHUD;
				TutorialText = TutorialWidget->Text_TutorialLine;
				StartTutorial();
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &ATutorielManager::InitializeTutorial, 0.1f, false);
			}
		}
	}
}

void ATutorielManager::ProceedNextStep()
{
	if (CurrentStep >= TutorialSteps.Num())
	{
		return;
	}

	UTutorialDialogue* CurrentDialogue = TutorialSteps[CurrentStep];

	if (CurrentLineIndex < CurrentDialogue->DialogueLines.Num())
	{
		const FTutorialDialogueLine& Line = CurrentDialogue->DialogueLines[CurrentLineIndex];
		TutorialText->SetText(Line.DialogueText);
		//UE_LOG(LogTemp, Log, TEXT("Displaying: %s"), *Line.DialogueText.ToString());
		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &ATutorielManager::ProceedNextStep, Line.DisplayDuration, false);
		CurrentLineIndex++;

	}
	else
	{
		CurrentStep++;
		CurrentLineIndex = 0;
		ProceedNextStep();
	}
}

// Called every frame
void ATutorielManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorielManager::StartTutorial()
{
	CurrentStep = 0;
	CurrentLineIndex = 0;
	ProceedNextStep();
}


