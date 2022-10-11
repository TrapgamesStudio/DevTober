// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cyberpunk_OctoberGameMode.h"
#include "Cyberpunk_OctoberCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACyberpunk_OctoberGameMode::ACyberpunk_OctoberGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/01_Blueprint/mainCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
