// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerEnums.h"
#include "DifficultyManager.generated.h"

USTRUCT()
struct FDifficulty
{
	GENERATED_BODY()

#define BonusPointsPerExtraObstacle 0.1f
#define BonusPointsPerModifier 0.1f

public:

	UPROPERTY()
		float GameSpeed = 2000.0f;

	UPROPERTY()
		uint8 ObstaclesPerTile = 4;

	UPROPERTY()
		uint8 ModifiersPerObstacle = 1;

	float ScorePerSecond() { return ScorePerSecond(*this); }

	static float ScorePerSecond(FDifficulty Difficulty)
	{
		return Difficulty.GameSpeed * (1
			+ (Difficulty.ObstaclesPerTile - 1) * BonusPointsPerExtraObstacle
			+ Difficulty.ModifiersPerObstacle * BonusPointsPerModifier);
	}

	FString ToString()
	{
		FString StringBuilder;
		StringBuilder += FString("Game Speed: ");
		StringBuilder += FString::SanitizeFloat(GameSpeed);
		StringBuilder += FString("\n");
		StringBuilder += FString("Obstacles Per Tile: ");
		StringBuilder += FString::FromInt(ObstaclesPerTile);
		StringBuilder += FString("\n");
		StringBuilder += FString("Modifiers Per Obstacle: ");
		StringBuilder += FString::FromInt(ModifiersPerObstacle);
		StringBuilder += FString("\n");
		StringBuilder += FString("Score per second: ");
		StringBuilder += FString::SanitizeFloat(ScorePerSecond());
		StringBuilder += FString("\n");
		return StringBuilder;
	}
};


class ENDLESSRUNNER_API DifficultyManager
{
public:
	DifficultyManager();
	~DifficultyManager();

public:
	//Send in the current difficulty each time a tile is spawned
	//If true, the difficulty has been changed.
	bool TryUpdateDifficulty(FDifficulty& CurrentDifficulty);

protected:

	//Counts how many times TryUpdateDifficulty has been called
	uint32 DifficultyUpdateRequests = 0;

	//These values describe the details of how often and how much
	//the  difficulty should increase.
	const uint32 SpeedUpdateFrequency = 5;
	const float SpeedChangeIncrements = 150.0f;

	const uint32 ObstacleUpdateFrequency = 30;
	const uint32 ObstacleUpdateDisplacement = 0;
	const uint32 ObstacleMaximum = 0;
	const uint32 ObstacleIncrements = 2;

	const uint32 ModifierUpdateFrequency = 30;
	const uint32 ModifierUpdateDisplacement = 15;
	const uint32 ModifierMaximum = (int)ObstacleModifier::Num;

	//This method will lower the speed of a Difficulty setting by Increments
	//Until Difficulty.GetScore is less than Score.
	//We use this when we've increased the obstacles/modifiers to lower the speed; 
	//that way the ScorePerSecond values are almost continuous over time.
	static void LowerSpeedToMatchScore(FDifficulty& Difficulty, float Score, float Increments);
};
