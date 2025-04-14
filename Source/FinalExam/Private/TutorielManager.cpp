// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorielManager.h"
#include "TutorialDialogue.h"
#include "MainCharacter.h"
#include "PlayerHUDWidget.h"
#include "BobbyActor.h"
#include "Engine/TargetPoint.h"

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

void ATutorielManager::TriggerEvent()
{
	OnTutorialEventTriggered.Broadcast();
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

		if (Bobby)
		{
			if (Line.bTriggerHello)
			{
				Bobby->SayHello();
			}
			if (Line.MoveToTargetIndex >= 0 && TargetPoints.IsValidIndex(Line.MoveToTargetIndex))
			{
				Bobby->MoveToLocation(TargetPoints[Line.MoveToTargetIndex]->GetActorLocation());
			}
		}

		if (Line.bWaitForEvent)
		{
			OnTutorialEventTriggered.AddDynamic(this, &ATutorielManager::ContinueDialogue);
			return;
		}

		CurrentLineIndex++;

		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &ATutorielManager::ProceedNextStep, Line.DisplayDuration, false);
	}
	else
	{
		CurrentStep++;
		CurrentLineIndex = 0;
		ProceedNextStep();
	}
}


void ATutorielManager::ContinueDialogue()
{
	OnTutorialEventTriggered.RemoveDynamic(this, &ATutorielManager::ContinueDialogue);
	CurrentLineIndex++;
	ProceedNextStep();
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


