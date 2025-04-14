// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TutorielManager.generated.h"

class UTutorialDialogue;
class UPlayerHUDWidget;
class ABobbyActor;
class ATargetPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTutorialEventTriggered);

UCLASS()
class FINALEXAM_API ATutorielManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorielManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dialogues")
	TArray<UTutorialDialogue*> TutorialSteps;

	int32 CurrentStep = 0;
	int32 CurrentLineIndex = 0;
	FTimerHandle DialogueTimerHandle;

	UPlayerHUDWidget* TutorialWidget = nullptr;

	UTextBlock* TutorialText = nullptr;


	void ProceedNextStep();

	UFUNCTION()
	void ContinueDialogue();

	UPROPERTY(EditAnywhere)
	ABobbyActor* Bobby;

	UPROPERTY(EditAnywhere,Category = "Bobby")
	TArray<ATargetPoint*> TargetPoints;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartTutorial();
	void InitializeTutorial();

	//UFUNCTION()
	void TriggerEvent();

	FOnTutorialEventTriggered OnTutorialEventTriggered;
};
