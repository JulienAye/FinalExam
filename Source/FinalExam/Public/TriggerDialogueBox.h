#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerDialogueBox.generated.h"

class UBoxComponent;
class ATutorielManager;

UCLASS()
class FINALEXAM_API ATriggerDialogueBox : public AActor
{
	GENERATED_BODY()

public:
	ATriggerDialogueBox();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, Category = "Tutorial")
	ATutorielManager* TutorielManager;

	bool bHasTriggeredTutorialEvent = false;

	UPROPERTY(EditAnywhere, Category = "Tutorial")
	bool bTriggerOnce = true;

	bool bHasTriggered = false;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


};
