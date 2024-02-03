#include "Tweener/TweenerBase.h"

#include "Components/TweeningComponent.h"

void UTweenerBase::StartTween(AActor* InTweenActor, const float InInterpTime, const FVector& InTo)
{
	From = InTweenActor->GetActorLocation();
	To = InTo;
	TweenOwner = InTweenActor;
	InterpTime = InInterpTime;
	bIsAttach = true;
	
	if(InTweenActor)
	{
		FTimerManager& TimerManager = InTweenActor->GetWorld()->GetTimerManager();
		TimerManager.SetTimer(TimerHandle_Tweening, this, &ThisClass::Interp, 1.f/60.f, true);
	}
}

void UTweenerBase::StartTweenFrom(AActor* InTweenActor, const float InInterpTime, const FVector& InFrom, const FVector& InTo)
{
	From = InFrom;
	To = InTo;
	TweenOwner = InTweenActor;
	InterpTime = InInterpTime;
	bIsAttach = false;
	
	if(InTweenActor)
	{
		FTimerManager& TimerManager = InTweenActor->GetWorld()->GetTimerManager();
		TimerManager.SetTimer(TimerHandle_Tweening, this, &ThisClass::Interp, 1.f/60.f, true);
	}
}

void UTweenerBase::Interp()
{
	FTimerManager& TimerManager = TweenOwner->GetWorld()->GetTimerManager();
	ElapsedTime += TimerManager.GetTimerRate(TimerHandle_Tweening);
	
	const FVector InterpPosition = FMath::Lerp(From, To, ElapsedTime/InterpTime);
	
	UE_LOG(LogTemp, Log, TEXT("InterpPosition: %s"), *InterpPosition.ToString());
	
	TweenOwner->SetActorLocation(InterpPosition);	

	if (FMath::IsNearlyEqual(InterpTime, ElapsedTime, 0.1f))
	{
		TimerManager.ClearTimer(TimerHandle_Tweening);

		if(bIsAttach) return;
		 if(UTweeningComponent* TweeningComponent = TweenOwner->FindComponentByClass<UTweeningComponent>())
		 {
		 	TweeningComponent->ActiveTweener = nullptr;
		 }		
	}
}