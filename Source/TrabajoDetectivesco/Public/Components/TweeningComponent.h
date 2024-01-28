#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TweeningComponent.generated.h"


class UTweenerBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRABAJODETECTIVESCO_API UTweeningComponent : public UActorComponent
{
	GENERATED_BODY()

	TObjectPtr<UTweenerBase> ActiveTweener;

	float TimeLerp = 1.f;

public:
	
	UFUNCTION(BlueprintCallable)
	UTweenerBase* StartTween(const FVector& To, float IntTime);

	float GetTimeLerp() const {return TimeLerp;};
	
};
