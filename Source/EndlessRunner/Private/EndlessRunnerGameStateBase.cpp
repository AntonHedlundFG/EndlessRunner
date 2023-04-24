// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameStateBase.h"

AEndlessRunnerGameStateBase::AEndlessRunnerGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == GameplayState::Play)
	{
		CurrentScore += DeltaTime * CurrentSpeed;
	}
}

void AEndlessRunnerGameStateBase::CollideWithObstacle()
{
	//Nothing happens if we're invulnerable or not playing
	if (!GetWorldTimerManager().IsTimerActive(CollisionTimerHandle) && CurrentState == GameplayState::Play)
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
	switch (CurrentState) {
	case GameplayState::Pause:
		CurrentState = GameplayState::Play;
		UGameplayStatics::SetGamePaused(this, false);
		OnGameplayStateChange.Broadcast(GameplayState::Play);
		break;
	case GameplayState::Play:
		CurrentState = GameplayState::Pause;
		UGameplayStatics::SetGamePaused(this, true);
		OnGameplayStateChange.Broadcast(GameplayState::Pause);
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
	CurrentState = NewState;
	OnGameplayStateChange.Broadcast(NewState);
}
void AEndlessRunnerGameStateBase::OnCollisionTimer()
{
	//Invulnerability end
}
void AEndlessRunnerGameStateBase::EndGame()
{
	
	//Maybe this should also include an "&& OnRequestNameInput.IsBound()"?
	if (HighScore.CheckRankFromScore(CurrentScore) < HighScore.ListSize)
	{
		SetState(GameplayState::WaitingForName);
		OnRequestNameInput.Broadcast();
	} else { SetState(GameplayState::Stop); }
}

void AEndlessRunnerGameStateBase::NameInputRequestResponse(FString Name)
{
	if (CurrentState != GameplayState::WaitingForName) { return; }

	HighScore.AddNewHighScore(Name, CurrentScore);
	OnHighScoreChange.Broadcast();
	CurrentState = GameplayState::Stop;
}