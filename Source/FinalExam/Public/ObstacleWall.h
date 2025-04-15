// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleWall.generated.h"

class AInteractiveButton;
class APressurePlate;

UCLASS()
class FINALEXAM_API AObstacleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WallMesh;

	UPROPERTY(EditAnywhere, Category = "Wall")
	TArray<AInteractiveButton*> Buttons;

	UPROPERTY(EditAnywhere, Category = "Wall")
	TArray<APressurePlate*> PressurePlates;

	UPROPERTY(EditAnywhere, Category = "Wall")
	float LoweredZOffset = -200.f;

	FVector InitialLocation;
	bool bIsLowered = false;

	bool AreAllConditionsMet() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void EvaluateConditions();

	void RegisterPressurePlate(class APressurePlate* PressurePlate);

	void RegisterButton(class AInteractiveButton* Button);
};
