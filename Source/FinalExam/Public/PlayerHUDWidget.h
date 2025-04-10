	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class FINALEXAM_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCloneCount(int32 Count);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CloneCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TutorialLine;

protected:
	virtual void NativeConstruct() override;

	
};
