// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"
#include "Components/ProgressBar.h"


void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UButtonWidget::SetProgress(float Ratio)
{
	if (ProgressBar)
	{
		ProgressBar->SetPercent(Ratio);
	}
}
