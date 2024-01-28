#include "Components/InspectableComponent.h"

#include "Components/BoxComponent.h"
#include "Components/TweeningComponent.h"
#include "Core/TrabajoDetectivescoCharacter.h"
#include "InspectableActor/InspectableActor.h"


UInspectableComponent::UInspectableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInspectableComponent::AttachActor(const ATrabajoDetectivescoCharacter* InCharacter) const
{
	AInspectableActor* InspectableActor = Cast<AInspectableActor>(GetOwner());
	if(!InspectableActor) return;

	UTweeningComponent* TweeningComponent = InspectableActor->FindComponentByClass<UTweeningComponent>();
	if(!TweeningComponent) return;

	// TArray<UActorComponent*> Components = InCharacter->GetComponentsByTag(USceneComponent::StaticClass(),"PointToInspect");
	//
	// USceneComponent* SceneComponent = nullptr;
	//
	// for(UActorComponent* Component : Components)
	// {
	// 	SceneComponent = Cast<USceneComponent>(Component);
	// 	FString NombreComp = SceneComponent->GetName();
	//
	// 	if(NombreComp.Equals("PointToInspect")) break;
	// }
	// if(SceneComponent)
	// {
	// 	TweeningComponent->StartTween(SceneComponent->GetComponentLocation(), TweeningComponent->GetTimeLerp());
	// }
	
	if(const USceneComponent* PointToInspect = InCharacter->FindComponentByClass<USceneComponent>()){
		TweeningComponent->StartTween(PointToInspect->GetComponentLocation(), TweeningComponent->GetTimeLerp());
	}	
}

void UInspectableComponent::InspectActor(const FInputActionValue& Value) const
{
	const FVector RotateAxis = Value.Get<FVector>();
	
	if(AInspectableActor* InspectableActor = Cast<AInspectableActor>(GetOwner()))
	{
		InspectableActor->AddActorLocalRotation(
			FQuat(FRotator(RotateAxis.Y,RotateAxis.Z,RotateAxis.X)),
			false,
			nullptr,
			ETeleportType::None);
	}
}