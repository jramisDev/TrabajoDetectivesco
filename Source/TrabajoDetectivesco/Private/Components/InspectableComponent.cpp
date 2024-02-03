#include "Components/InspectableComponent.h"

#include "Components/TweeningComponent.h"
#include "Core/TrabajoDetectivescoCharacter.h"
#include "InspectableActor/InspectableActor.h"


UInspectableComponent::UInspectableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInspectableComponent::AttachActor(ATrabajoDetectivescoCharacter* InCharacter) const
{
	AInspectableActor* InspectableActor = Cast<AInspectableActor>(GetOwner());
	if(!InspectableActor) return;

	UTweeningComponent* TweeningComponent = InspectableActor->FindComponentByClass<UTweeningComponent>();
	if(!TweeningComponent) return;

	if(!InCharacter) return;
	
	TweeningComponent->StartTween(InCharacter->GetLocationInspectPoint());

}

void UInspectableComponent::DesAttachActor(ATrabajoDetectivescoCharacter* InCharacter) const
{
	AInspectableActor* InspectableActor = Cast<AInspectableActor>(GetOwner());
	if(!InspectableActor) return;

	UTweeningComponent* TweeningComponent = InspectableActor->FindComponentByClass<UTweeningComponent>();
	if(!TweeningComponent) return;

	if(!InCharacter) return;
	
	TweeningComponent->StartTweenFrom(InCharacter->GetLocationInspectPoint(), InspectableActor->GetStartLocation());

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