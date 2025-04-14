// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CloneBonus.generated.h"

UCLASS()
class FINALEXAM_API ACloneBonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloneBonus();

protected:

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	class USphereComponent* SphereCollision;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
