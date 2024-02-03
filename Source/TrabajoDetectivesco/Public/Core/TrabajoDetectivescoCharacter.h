// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TrabajoDetectivescoCharacter.generated.h"

class AInspectableActor;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ATrabajoDetectivescoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	
	//Inspect variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InspectView, meta = (AllowPrivateAccess = "true"))
	FVector PointToInspect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InspectView, meta = (AllowPrivateAccess = "true"))
	float DistanceInspect = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InspectView, meta=(AllowPrivateAccess = "true"))
	class UInputAction* InspectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InspectView, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookItemAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InspectView, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* InspectMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=InspectView, meta = (AllowPrivateAccess = "true"))
	AInspectableActor* InspectableActor;

	
public:
	ATrabajoDetectivescoCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	
	void Move(const FInputActionValue& Value);	
	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	void ThrowInspectMode();
	void RemoveInspectMode();

	void InspectActor();
	void LookItem(const FInputActionValue& Value);
	
	void AddMappingContext(const UInputMappingContext* InOldMappingContext, const UInputMappingContext* InNewMappingContext) const;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//Le sumamos 25 puntos en altura para que quede a la altura de la camara
	FVector GetLocationInspectPoint() const { return (this->GetActorLocation()+FVector(0.f,0.f,25.f) + this->GetActorForwardVector() * 100.f); } 
	
};

