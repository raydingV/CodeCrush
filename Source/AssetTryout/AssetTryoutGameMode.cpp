// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetTryoutGameMode.h"
#include "AssetTryoutCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssetTryoutGameMode::AAssetTryoutGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
