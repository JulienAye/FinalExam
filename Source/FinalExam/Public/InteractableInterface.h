#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class FINALEXAM_API IInteractableInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(ACharacter* InteractingCharacter) = 0;

protected:
	
	virtual bool IsActivated() const = 0;
};
