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