﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TweenerBase.generated.h"


UCLASS()
class TRABAJODETECTIVESCO_API UTweenerBase : public UObject
{
	GENERATED_BODY()

	friend class UTweeningComponent;

	AActor* TweenOwner;	
	FVector From, To;	
	
	FTimerHandle TimerHandle_Tweening;

	float ElapsedTime = -1.f;	
	float InterpTime;


protected:
	
	void StartTween(AActor* InTweenActor, const float InInterpTime, const FVector& InTo);
	void Interp();
};