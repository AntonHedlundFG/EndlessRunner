// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreManager.generated.h"

#define HIGH_SCORE_FILE_NAME "HighScores.json"

USTRUCT(BlueprintType)
struct FHighScore
{
	GENERATED_BODY()
		
public:
	
	UPROPERTY()
		FString Name;

	UPROPERTY()
	uint32 Score;

	bool operator<(const FHighScore& Other) const
	{
		return Score < Other.Score;
	}

	bool operator>(const FHighScore& Other) const
	{
		return Score > Other.Score;
	}
	bool operator<=(const FHighScore& Other) const
	{
		return Score <= Other.Score;
	}

	bool operator>=(const FHighScore& Other) const
	{
		return Score >= Other.Score;
	}

};


class ENDLESSRUNNER_API HighScoreManager
{
public:
	HighScoreManager();
	~HighScoreManager();

	FHighScore TestComparison();

	TArray<FHighScore> HighScores;

	uint16 ListSize = 3;

	FString HighScoreFilePath;

	void FillBlankScores();

	void LoadHighScores();
	void SaveHighScores();
};
