// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FINALEXAM_API AJuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	bool bIsInTutorial = true;
	
};
