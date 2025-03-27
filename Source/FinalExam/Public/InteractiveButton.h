#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractiveButton.generated.h"

class ADoor;

UCLASS()
class FINALEXAM_API AInteractiveButton : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInteractiveButton();

	//virtual void Tick(float DeltaTime) override;

	virtual void Interact(ACharacter* InteractingCharacter) override;
	bool IsActivated() const override { return bIsActivated; }

	void UpdateButtonMaterial();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsActivated = false;

	UPROPERTY(EditAnywhere, Category = "Button|Material")
	UMaterialInterface* ActivatedMaterial;

	UPROPERTY(EditAnywhere, Category = "Button|Material")
	UMaterialInterface* DeactivatedMaterial;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonMesh; //To change the material of the button

	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<ADoor*> LinkedDoors; //To store the actors that will be affected by the button

	UPROPERTY(EditAnywhere, Category = "Button|Sound")
	USoundBase* InteractSound;
};
