// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CinematicManager.generated.h"

UCLASS()
class FINALEXAM_API ACinematicManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACinematicManager();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Cinematic")
	void ShowCredits();
};
