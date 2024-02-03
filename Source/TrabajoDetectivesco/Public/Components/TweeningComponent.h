#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TweeningComponent.generated.h"


class UTweenerBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRABAJODETECTIVESCO_API UTweeningComponent : public UActorComponent
{
	GENERATED_BODY()
	
	const float TimeLerp = 1.f;

public:
	
	TObjectPtr<UTweenerBase> ActiveTweener;
	
	UFUNCTION(BlueprintCallable)
	UTweenerBase* StartTween(const FVector& InTo);
	
	UFUNCTION(BlueprintCallable)
	UTweenerBase* StartTweenFrom(const FVector& InFrom, const FVector& InTo);
	
};
