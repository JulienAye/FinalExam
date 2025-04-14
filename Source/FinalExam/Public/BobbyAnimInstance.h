// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BobbyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINALEXAM_API UBobbyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	bool bIsSayingHello;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	bool bIsMoving;
	
};
