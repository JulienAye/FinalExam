// Fill out your copyright notice in the Description page of Project Settings.


#include "CloneWidget.h"
#include "Components/ProgressBar.h"

void UCloneWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCloneWidget::SetLifeRatio(float Ratio)
{
	if (ProgressBar_Life)
	{
		ProgressBar_Life->SetPercent(Ratio);
	}
}

