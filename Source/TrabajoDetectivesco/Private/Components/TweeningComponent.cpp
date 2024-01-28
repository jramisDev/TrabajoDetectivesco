#include "Components/TweeningComponent.h"

#include "Tweener/TweenerBase.h"

UTweenerBase* UTweeningComponent::StartTween(const FVector& To, const float IntTime)
{
	if(!ActiveTweener)
	{
		ActiveTweener = NewObject<UTweenerBase>(this, UTweenerBase::StaticClass());
		if (ActiveTweener)
		{
			ActiveTweener->StartTween(GetOwner(), IntTime, To);
		}
	}
	return ActiveTweener;
}