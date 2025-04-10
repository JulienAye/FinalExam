// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TutorialDialogue.generated.h"


USTRUCT(BlueprintType)
struct FTutorialDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DisplayDuration = 3.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bWaitForEvent = false;
};

UCLASS()
class FINALEXAM_API UTutorialDialogue : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FTutorialDialogueLine> DialogueLines;
	
};
