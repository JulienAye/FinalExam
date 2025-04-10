// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.h"
void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetCloneCount(0);

	//if(PlayerHUDClass)
	//{
	//	PlayerHUD = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDClass);
	//	if (PlayerHUD)
	//	{
	//		PlayerHUD->AddToViewport();
	//	}
	//}
}

void UPlayerHUDWidget::SetCloneCount(int32 Count)
{
	if (Text_CloneCount)
	{
		Text_CloneCount->SetText(FText::AsNumber(Count));
	}
}