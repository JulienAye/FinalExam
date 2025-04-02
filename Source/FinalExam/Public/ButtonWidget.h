// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

class UProgressBar;

UCLASS()
class FINALEXAM_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetProgress(float Ratio);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
};
