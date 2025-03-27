// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class ACloneCharacter;
struct FInputActionValue;

UCLASS()
class FINALEXAM_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Crouch(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void UseInteract(const FInputActionValue& Value);
	void SpawnClone(const FInputActionValue& Value);

	int32 MaxHp = 1;
	int32 CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clone")
	int32 AvailableClones = 1; //At start the player will be able to create only 1 clone


	float valueAim = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SpawnCloneAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	bool bSprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch", meta = (AllowPrivateAccess = "true"))
	bool bCrouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch", meta = (AllowPrivateAccess = "true"))
	bool bInteract = false;

	UPROPERTY(EditAnywhere, Category = "Clone")
	TSubclassOf<class ACloneCharacter> CloneClass;

	UPROPERTY()
	TArray<ACloneCharacter*> ActiveClones;
};
