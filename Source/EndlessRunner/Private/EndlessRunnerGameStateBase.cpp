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
	//Nothing happens if we're invulnerable
	if (!GetWorldTimerManager().IsTimerActive(CollisionTimerHandle))
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
	SetState(GameplayState::Stop);

	//Simple, needs input screen
	HighScore.AddNewHighScore(FString("New Score"), CurrentScore);
}