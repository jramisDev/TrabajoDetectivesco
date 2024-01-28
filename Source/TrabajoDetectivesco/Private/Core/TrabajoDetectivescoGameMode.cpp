// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/TrabajoDetectivescoGameMode.h"
#include "Core/TrabajoDetectivescoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATrabajoDetectivescoGameMode::ATrabajoDetectivescoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
