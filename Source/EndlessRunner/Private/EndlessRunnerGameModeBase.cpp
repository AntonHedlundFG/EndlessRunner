// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

void AEndlessRunnerGameModeBase::InitGameState()
{
	Super::InitGameState();
	InitEndlessGameState();
	
}

void AEndlessRunnerGameModeBase::InitEndlessGameState()
{
	EndlessGameState = Cast<AEndlessRunnerGameStateBase>(GameState);
	EndlessGameState->SetMaxLives(MaxLives);
	EndlessGameState->InvulnerableDuration = InvulnerableDuration;
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(this, -1, true);
}