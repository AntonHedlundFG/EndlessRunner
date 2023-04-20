// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreManager.generated.h"

#define HIGH_SCORE_FILE_NAME "HighScores.json"

//This struct describes a single entry in the HighScore array.
USTRUCT(BlueprintType)
struct FHighScore
{
	GENERATED_BODY()
		
public:
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	uint32 Score;

#pragma region Comparative operator overloading
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

	bool operator<(const uint32 OtherScore) const
	{
		return Score < OtherScore;
	}

	bool operator>(const uint32 OtherScore) const
	{
		return Score > OtherScore;
	}
	bool operator<=(const uint32 OtherScore) const
	{
		return Score <= OtherScore;
	}

	bool operator>=(const uint32 OtherScore) const
	{
		return Score >= OtherScore;
	}
#pragma endregion

};

//This struct lists all entries in the HighScore array
//It is only required to manage Json conversion
USTRUCT(BlueprintType)
struct FHighScores
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FHighScore> HighScores;

	void SetHighScores(TArray<FHighScore> HighScoresIn)
	{
		HighScores.Empty();
		for (int i = 0; i < HighScoresIn.Num(); i++) 
		{
			HighScores.Add(HighScoresIn[i]);
		}
	}
};


class ENDLESSRUNNER_API HighScoreManager
{
public:
	HighScoreManager();
	~HighScoreManager();

	//How many HighScores should be stored
	uint8 const ListSize = 3;

	//Checks which place on the leaderboard a new score would get
	//Returns ListSize if none.
	uint8 CheckRankFromScore(uint32 Score);

	//Tries adding a new result to the leaderboard. Returns false if score too low.
	bool AddNewHighScore(FString name, uint32 Score);

	//Array storing HighScores during play, sorted highest->lowest
	TArray<FHighScore> HighScores;

private:

	//Pads HighScores array with fake values if HighScores.Num() < ListSize
	void FillBlankScores();

	//Stores path to file named in HIGH_SCORE_FILE_NAME
	FString HighScoreFilePath;

	//Loads and saves from Json file
	void LoadHighScores();
	void SaveHighScores();
};
