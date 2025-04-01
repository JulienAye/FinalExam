// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CloneWidget.generated.h"

class UProgressBar;

UCLASS()
class FINALEXAM_API UCloneWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetLifeRatio(float Ratio);

protected:


};
