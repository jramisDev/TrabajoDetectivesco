#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InspectableComponent.generated.h"


struct FInputActionValue;
class ATrabajoDetectivescoCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRABAJODETECTIVESCO_API UInspectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInspectableComponent();

	void AttachActor(ATrabajoDetectivescoCharacter* InCharacter) const;
	void DesAttachActor(ATrabajoDetectivescoCharacter* InCharacter) const;
	void InspectActor(const FInputActionValue& Value) const;

};
