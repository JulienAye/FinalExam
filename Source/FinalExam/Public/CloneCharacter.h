// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "CloneCharacter.generated.h"

class UProgressBar;

UCLASS()
class FINALEXAM_API ACloneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACloneCharacter();

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* CloneWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CloneWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Material")
	UMaterialInstanceDynamic* DissolveMaterial;

		 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box")
	UBoxComponent* InteractionBox;

	UPROPERTY()
	TArray<AActor*> ActorsToInteract;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CloneInteract();

	UFUNCTION()
	void DestroyClone();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	FTimerHandle TimerHandle;

	float LifeDuration = 7.f;
	float LifeRemaining;

};
