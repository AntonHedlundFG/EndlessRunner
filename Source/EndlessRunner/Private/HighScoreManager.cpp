// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreManager.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/FileHelper.h"
#include "JsonObjectConverter.h"

HighScoreManager::HighScoreManager()
{
	HighScoreFilePath = FPaths::ProjectSavedDir() + FString(HIGH_SCORE_FILE_NAME);

	//Loads HighScores from file on construction
	LoadHighScores();
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::FillBlankScores()
{
	for (int i = HighScores.Num(); i < ListSize; i++) 
	{
		AddNewHighScore(FString("NoName") + FString::FromInt(i), std::rand() % 10);
	}
}

void HighScoreManager::LoadHighScores()
{
	//Loads file content into Json string format, fails if file does not exist.
	FString JSONStringArray;
	if (FFileHelper::LoadFileToString(JSONStringArray, *HighScoreFilePath))
	{
		//Converts Json string into FHighScores struct
		FHighScores OutHighScores;
		FJsonObjectConverter::JsonObjectStringToUStruct<FHighScores>(JSONStringArray, &OutHighScores);
		
		//Update the HighScores array with contents of FHighScores struct.
		for (int i = 0; i < OutHighScores.HighScores.Num(); i++) 
		{
			HighScores.Add(OutHighScores.HighScores[i]);
		}
	}

	//Called in case the file contains fewer entries than ListSize or does not exist
	FillBlankScores();
}

void HighScoreManager::SaveHighScores()
{
	//Generates a FHighScores struct for file storage
	FString JSONStringArray;
	FHighScores InHighScores;
	InHighScores.SetHighScores(HighScores);

	//Converts FHighScores struct into Json string format
	FJsonObjectConverter::UStructToJsonObjectString<FHighScores>(InHighScores, JSONStringArray);

	//Stores Json string in designated file (creates file if non-existent)
	FFileHelper::SaveStringToFile(JSONStringArray, *HighScoreFilePath);
}

uint8 HighScoreManager::CheckRankFromScore(uint32 Score)
{
	for (int i = 0; i < HighScores.Num(); i++) 
	{
		if (HighScores[i] < Score)
			return i;
	}
	return ListSize;
}

bool HighScoreManager::AddNewHighScore(FString Name, uint32 Score)
{
	uint8 Rank = CheckRankFromScore(Score);
	
	//Leaderboard is full; score is too low to place.
	if (Rank == ListSize && HighScores.Num() >= ListSize) { return false; }

	//Score is too low to place, but there's empty room in the leaderboard
	//Rank is set to be the highest empty spot
	if (Rank == ListSize) { Rank = HighScores.Num(); }

	//Insert the new score into the HighScores array at the desired rank.
	FHighScore NewScore;
	NewScore.Name = Name;
	NewScore.Score = Score;
	HighScores.Insert(NewScore, Rank);

	//If HighScores array is longer than ListSize, remove the lowest score.
	if (HighScores.Num() > ListSize) { HighScores.Pop(); }
	
	//Since a new score has been added, save to file.
	SaveHighScores();

	return true;
}

FString HighScoreManager::GetString()
{
	FString StringBuilder;
	StringBuilder += FString("Leaderboard: \n");
	for (int i = 0; i < HighScores.Num(); i++) 
	{
		StringBuilder += HighScores[i].Name;
		StringBuilder += FString(": ");
		StringBuilder += FString::FromInt(HighScores[i].Score);
		StringBuilder += FString("\n");
	}
	return StringBuilder;
}