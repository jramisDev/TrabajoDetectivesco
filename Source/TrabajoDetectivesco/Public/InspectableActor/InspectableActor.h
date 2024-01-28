#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InspectableActor.generated.h"

class UTweeningComponent;
class UInspectableComponent;

UCLASS()
class TRABAJODETECTIVESCO_API AInspectableActor : public AActor
{
	GENERATED_BODY()

public:

	AInspectableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UInspectableComponent* InspectableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UTweeningComponent* TweeningComponent;

};

