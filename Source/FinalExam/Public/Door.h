// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class AInteractiveButton;
class APressurePlate;

UCLASS()
class FINALEXAM_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RegisterButton(class AInteractiveButton* Button);
	void RegisterPressurePlate(class APressurePlate* PressurePlate);
	void EvaluateDoorCondition();

	void OpenDoor();
	void CloseDoor();

	UPROPERTY(EditAnywhere, Category = "Door")
	int32 RequiredButtons; 

	UPROPERTY(EditAnywhere, Category = "PressurePlate")
	int32 RequiredPressurePlates;

	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<AInteractiveButton*> LinkedButtons;

	UPROPERTY(EditAnywhere, Category = "PressurePlate")
	TArray<APressurePlate*> LinkedPressurePlates;

	bool bIsOpen;

private:
	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* DoorMesh;

	FVector InitialLocation;

	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Door")
	float DoorSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenHeight = 200.f;
};
