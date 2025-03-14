// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptStalkerGameMode.h"
#include "CryptStalkerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptStalkerGameMode::ACryptStalkerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
