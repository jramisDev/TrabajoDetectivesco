#include "Components/TweeningComponent.h"

#include "Tweener/TweenerBase.h"

UTweenerBase* UTweeningComponent::StartTween(const FVector& InTo)
{
	if(!ActiveTweener)
	{
		ActiveTweener = NewObject<UTweenerBase>(this, UTweenerBase::StaticClass());
		if (ActiveTweener)
		{
			ActiveTweener->StartTween(GetOwner(), TimeLerp, InTo);
		}
	}
	return ActiveTweener;
}

UTweenerBase* UTweeningComponent::StartTweenFrom(const FVector& InFrom, const FVector& InTo)
{
	//if(!ActiveTweener)
	//{
		//ActiveTweener = NewObject<UTweenerBase>(this, UTweenerBase::StaticClass());
		if (ActiveTweener)
		{
			ActiveTweener->StartTweenFrom(GetOwner(), TimeLerp, InFrom, InTo);
		}

	return ActiveTweener;
}