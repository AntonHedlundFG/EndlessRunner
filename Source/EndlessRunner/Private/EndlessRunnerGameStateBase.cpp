// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameStateBase.h"

void AEndlessRunnerGameStateBase::RemoveLife()
{
	CurrentLives--;
	UKismetSystemLibrary::PrintString(this, FString::FromInt(CurrentLives));
}
void AEndlessRunnerGameStateBase::SetMaxLives(int lives)
{
	CurrentLives = lives;
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