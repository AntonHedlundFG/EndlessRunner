// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameStateBase.h"

AEndlessRunnerGameStateBase::AEndlessRunnerGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Very simple score calculation, should be improved to take number of 
	//obstacles spawned into account.
	if (CurrentGameplayState == GameplayState::Play)
	{
		CurrentScore += DeltaTime * CurrentDifficulty.ScorePerSecond();
	}
}

void AEndlessRunnerGameStateBase::CollideWithObstacle()
{
	//Nothing happens if we're invulnerable or not playing
	if (!GetWorldTimerManager().IsTimerActive(CollisionTimerHandle) && CurrentGameplayState == GameplayState::Play)
	{
		if (--CurrentLives <= 0) 
		{
			EndGame();
		}
		else
		{
			//Invulnerability start
			GetWorldTimerManager().SetTimer(CollisionTimerHandle, this, &AEndlessRunnerGameStateBase::OnCollisionTimer, InvulnerableDuration, false);
		}
	}
}
void AEndlessRunnerGameStateBase::InputPause() 
{
	switch (CurrentGameplayState) {
	case GameplayState::Pause:
		SetState(GameplayState::Play);
		UGameplayStatics::SetGamePaused(this, false);
		break;
	case GameplayState::Play:
		SetState(GameplayState::Pause);
		UGameplayStatics::SetGamePaused(this, true);
		break;
	}
}
void AEndlessRunnerGameStateBase::SetMaxLives(int Lives)
{
	CurrentLives = Lives;
}
void AEndlessRunnerGameStateBase::SetSpeed(float NewSpeed)
{
	CurrentSpeed = NewSpeed;
	OnGameSpeedChange.Broadcast(NewSpeed);
}
void AEndlessRunnerGameStateBase::SetState(GameplayState NewState)
{
	CurrentGameplayState = NewState;
	OnGameplayStateChange.Broadcast(NewState);
}
void AEndlessRunnerGameStateBase::OnCollisionTimer()
{
	//Invulnerability end
}
void AEndlessRunnerGameStateBase::EndGame()
{
	//Checks to see if the final score places on the leaderboard
	//If it does, request name input from UI
	//Otherwise, starts a timer to reset the game.
	if (HighScore.CheckRankFromScore(CurrentScore) < HighScore.ListSize)
	{
		SetState(GameplayState::WaitingForName);
		OnRequestNameInput.Broadcast();
	} else 
	{ 
		SetState(GameplayState::Stop);
		GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &AEndlessRunnerGameStateBase::ResetGame, ResetGameDuration, false);
	}
}

void AEndlessRunnerGameStateBase::NameInputRequestResponse(FString Name)
{
	if (CurrentGameplayState != GameplayState::WaitingForName) { return; }

	HighScore.AddNewHighScore(Name, CurrentScore);
	OnHighScoreChange.Broadcast();
	SetState(GameplayState::Stop);
	GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &AEndlessRunnerGameStateBase::ResetGame, ResetGameDuration, false);
}

void AEndlessRunnerGameStateBase::ResetGame()
{
	//Reloads the current level
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AEndlessRunnerGameStateBase::TileSpawned()
{
	if (DifficultyManagerInstance.TryUpdateDifficulty(CurrentDifficulty))
	{
		OnGameDifficultyChange.Broadcast(CurrentDifficulty);
	}
}