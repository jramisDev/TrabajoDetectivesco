#include "InspectableActor/InspectableActor.h"

#include "Components/InspectableComponent.h"
#include "Components/TweeningComponent.h"

AInspectableActor::AInspectableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	MeshComponent->SetupAttachment(RootComponent);	

#if WITH_EDITOR
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	
	if(StaticMeshFinder.Succeeded()) MeshComponent->SetStaticMesh(StaticMeshFinder.Object);
	
#endif

	InspectableComponent = CreateDefaultSubobject<UInspectableComponent>(TEXT("InspectableComponent"));

	TweeningComponent = CreateDefaultSubobject<UTweeningComponent>(TEXT("TweenerComponent"));
	
	
}

void AInspectableActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}
