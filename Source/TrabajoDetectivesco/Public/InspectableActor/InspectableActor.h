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

	FVector GetStartLocation() const { return StartLocation; } 

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true));
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true));
	UInspectableComponent* InspectableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true));
	UTweeningComponent* TweeningComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true));
	FVector StartLocation;

	virtual void BeginPlay() override;
	

};

