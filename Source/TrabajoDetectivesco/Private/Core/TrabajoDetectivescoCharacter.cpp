// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/TrabajoDetectivescoCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VectorUtil.h"
#include "Components/BoxComponent.h"
#include "Components/InspectableComponent.h"
#include "InspectableActor/InspectableActor.h"


//////////////////////////////////////////////////////////////////////////
// ATrabajoDetectivescoCharacter

ATrabajoDetectivescoCharacter::ATrabajoDetectivescoCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PointToInspect = CreateDefaultSubobject<USceneComponent>(TEXT("PointToInspect"));
	PointToInspect->SetRelativeLocation({90.f,0.f,60.f});

}

void ATrabajoDetectivescoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void ATrabajoDetectivescoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATrabajoDetectivescoCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATrabajoDetectivescoCharacter::Look);




		
		//Inspect
		EnhancedInputComponent->BindAction(InspectAction, ETriggerEvent::Started, this, &ATrabajoDetectivescoCharacter::InspectActor);

		//Inspect
		EnhancedInputComponent->BindAction(LookItemAction, ETriggerEvent::Triggered, this, &ATrabajoDetectivescoCharacter::LookItem);
	}
}

void ATrabajoDetectivescoCharacter::AddMappingContext(const UInputMappingContext* InOldMappingContext, const UInputMappingContext* InNewMappingContext) const
{
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InOldMappingContext);
			Subsystem->AddMappingContext(InNewMappingContext, 0);
		}
	}
}


void ATrabajoDetectivescoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATrabajoDetectivescoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		
	}
}

void ATrabajoDetectivescoCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATrabajoDetectivescoCharacter::GetHasRifle()
{
	return bHasRifle;
}





void ATrabajoDetectivescoCharacter::ThrowInspectMode()
{
	FHitResult OutHit;

	float RadiusSphere = 50.f;
		
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(RadiusSphere);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
					
	GetWorld()->SweepSingleByChannel(
		OutHit,
		this->GetActorLocation(),
		this->GetActorLocation() + this->GetActorForwardVector() * 100.f,
		FQuat::Identity,
		ECC_Visibility,
		CollisionShape,
		QueryParams
	);
		
#if WITH_EDITOR
	DrawDebugSphere(GetWorld(),
	                this->GetActorLocation(),
	                RadiusSphere,
	                100,
	                FColor::Blue,
	                false,
	                5.f
	);
#endif

	if (OutHit.IsValidBlockingHit())
	{
		if(UInspectableComponent* InspectableComponent = OutHit.GetActor()->FindComponentByClass<UInspectableComponent>())
		{
			InspectableComponent->AttachActor(this);
			IsInspecting = true;
			
			if(AInspectableActor* Insp = Cast<AInspectableActor>(OutHit.GetActor())) InspectableActor = Insp;
			
			AddMappingContext(DefaultMappingContext, InspectMappingContext);
		}
	}
}

void ATrabajoDetectivescoCharacter::RemoveInspectMode()
{
	AddMappingContext(InspectMappingContext, DefaultMappingContext);
	IsInspecting = false;
}

void ATrabajoDetectivescoCharacter::InspectActor()
{
	if(!IsInspecting)
	{	
		ThrowInspectMode();
	}else
	{
		RemoveInspectMode();
	}
}

void ATrabajoDetectivescoCharacter::LookItem(const FInputActionValue& Value)
{
	const FVector LookAxisVector = Value.Get<FVector>();

	if(UInspectableComponent* InspectableComponent = InspectableActor->FindComponentByClass<UInspectableComponent>())
	{
		InspectableComponent->InspectActor(LookAxisVector);
	}
}
