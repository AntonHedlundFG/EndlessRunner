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

	LoadHighScores();
	SaveHighScores();
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::FillBlankScores()
{
	for (int i = HighScores.Num(); i < ListSize; i++) 
	{
		FHighScore EmptyScore;
		EmptyScore.Name = FString("NoName");
		EmptyScore.Score = 0;
		HighScores.Add(EmptyScore);
	}
}

void HighScoreManager::LoadHighScores()
{
	FString JSONStringArray;
	FHighScores OutHighScores;
	if (FFileHelper::LoadFileToString(JSONStringArray, *HighScoreFilePath))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct<FHighScores>(JSONStringArray, &OutHighScores);
		for (int i = 0; i < OutHighScores.HighScores.Num(); i++) 
		{
			HighScores.Add(OutHighScores.HighScores[i]);
		}
	}

	//LOADFROMFILE
	FillBlankScores();
}

void HighScoreManager::SaveHighScores()
{
	FString JSONStringArray;
	FHighScores InHighScores;
	InHighScores.SetHighScores(HighScores);

	FJsonObjectConverter::UStructToJsonObjectString<FHighScores>(InHighScores, JSONStringArray);

	FFileHelper::SaveStringToFile(JSONStringArray, *HighScoreFilePath);
}