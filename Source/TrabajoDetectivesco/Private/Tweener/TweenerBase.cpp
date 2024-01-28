#include "Tweener/TweenerBase.h"

void UTweenerBase::StartTween(AActor* InTweenActor, const float InInterpTime, const FVector& InTo)
{
	From = InTweenActor->GetActorLocation();
	To = InTo;
	TweenOwner = InTweenActor;
	InterpTime = InInterpTime;
	
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
	TweenOwner->SetActorLocation(InterpPosition);
	

	if (FMath::IsNearlyEqual(InterpTime, ElapsedTime, 0.01f))
	{
		TimerManager.ClearTimer(TimerHandle_Tweening);
	}
}