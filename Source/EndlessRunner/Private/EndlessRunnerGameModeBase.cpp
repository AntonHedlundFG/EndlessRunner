// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameModeBase.h"
#include "EndlessRunnerGameStateBase.h"

void AEndlessRunnerGameModeBase::InitGameState()
{
	Super::InitGameState();
	
	// Send values to the GameState
	TObjectPtr<AEndlessRunnerGameStateBase> EndlessGameState = Cast<AEndlessRunnerGameStateBase>(GameState);
	EndlessGameState->SetMaxLives(MaxLives);
	EndlessGameState->InvulnerableDuration = InvulnerableDuration;
	
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//The gamemode already spawns one character automatically, this spawns the second one
	//in the first empty PlayerStart object.
	UGameplayStatics::CreatePlayer(this, -1, true);
}