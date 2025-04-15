#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ADoor;
class AObstacleWall;

UCLASS()
class FINALEXAM_API APressurePlate : public AActor
{
	GENERATED_BODY()

public:
	APressurePlate();


	bool bIsActivated;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<ADoor*> LinkedDoors;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInterface* ActiveMaterial;

	UPROPERTY(EditAnywhere)
	TArray<AObstacleWall*> LinkedWalls;
};
