// Fill out your copyright notice in the Description page of Project Settings.


#include "DifficultyManager.h"

DifficultyManager::DifficultyManager()
{
}

DifficultyManager::~DifficultyManager()
{
}

bool DifficultyManager::TryUpdateDifficulty(FDifficulty& Difficulty)
{
	DifficultyUpdateRequests++;

	//The if statement will be true once every "ObstacleUpdateFrequency" updates, starting at
	//"ObstacleUpdateDisplacement" if above 0, otherwise the first time happens after 
	//"ObstacleUpdateFrequency" updates. 
	//Only true if we haven't reached maximum obstacle amount or have no limit.
	if (((DifficultyUpdateRequests + ObstacleUpdateDisplacement) % ObstacleUpdateFrequency == 0)
		&& (ObstacleMaximum <= 0 || ObstacleMaximum > Difficulty.ObstaclesPerTile))
	{
		float PreviousScore = Difficulty.ScorePerSecond();
		Difficulty.ObstaclesPerTile += ObstacleIncrements;
		LowerSpeedToMatchScore(Difficulty, PreviousScore, SpeedChangeIncrements / 10.0f);
		return true;
	}

	//Same logic as above, but for modifiers per obstacle
	if (((DifficultyUpdateRequests + ModifierUpdateDisplacement) % ModifierUpdateFrequency == 0)
		&& (ModifierMaximum <= 0 || ModifierMaximum > Difficulty.ModifiersPerObstacle))
	{
		float PreviousScore = Difficulty.ScorePerSecond();
		Difficulty.ModifiersPerObstacle++;
		LowerSpeedToMatchScore(Difficulty, PreviousScore, SpeedChangeIncrements / 10.0f);
		return true;
	}

	if (DifficultyUpdateRequests % SpeedUpdateFrequency == 0)
	{
		Difficulty.GameSpeed += SpeedChangeIncrements;
		return true;
	}

	return false;
}

void DifficultyManager::LowerSpeedToMatchScore(FDifficulty& Difficulty, float Score, float Increments)
{
	while (Difficulty.ScorePerSecond() > Score) {
		Difficulty.GameSpeed -= Increments;
	}
}