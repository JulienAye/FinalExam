#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveButton.generated.h"

class ADoor;
class UButtonWidget;

UCLASS()
class FINALEXAM_API AInteractiveButton : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AInteractiveButton();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ACharacter* InteractingCharacter) override;
	bool IsActivated() const override { return bIsActivated; }

	void UpdateButtonMaterial();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsActivated = false;

	UPROPERTY(EditAnywhere, Category = "Button|Material")
	UMaterialInterface* ActivatedMaterial;

	UPROPERTY(EditAnywhere, Category = "Button|Material")
	UMaterialInterface* DeactivatedMaterial;

	void ResetButton();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonMesh; //To change the material of the button

	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<ADoor*> LinkedDoors; //To store the actors that will be affected by the button

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* InteractSound;

	FTimerHandle ResetTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* ButtonUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ButtonWidgetClass;

	UButtonWidget* TimerWidget = nullptr;

	float TimerDuration = 5.f;
	float TimeRemaining;
};
