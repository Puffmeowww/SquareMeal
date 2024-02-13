// Copyright Epic Games, Inc. All Rights Reserved.

#include "SquareMealGameMode.h"
#include "SquareMealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASquareMealGameMode::ASquareMealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
