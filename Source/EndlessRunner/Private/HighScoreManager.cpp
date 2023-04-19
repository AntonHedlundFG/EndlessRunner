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
	if (FFileHelper::LoadFileToString(JSONStringArray, *HighScoreFilePath))
	{
		//FJsonObjectConverter::JsonArrayStringToUStruct(JSONStringArray, &HighScores);
		//FJsonObjectConverter::JsonObjectStringToUStruct(JSONStringArray, &HighScores);
	}

	//LOADFROMFILE
	FillBlankScores();
}

void HighScoreManager::SaveHighScores()
{
	//The string where we store the entire array.
	FString JSONStringArray;

	//Iterate through the array, serializing each element and adding it to the array string.
	for (int i = 0; i < HighScores.Num(); i++) 
	{
		FHighScore HighScoreElement = HighScores[i];
		FString JSONStringElement;
		FJsonObjectConverter::UStructToJsonObjectString<FHighScore>(HighScoreElement, JSONStringElement);
		JSONStringArray += JSONStringElement;
	}

	//Write the array string into the savefile.
	FFileHelper::SaveStringToFile(JSONStringArray, *HighScoreFilePath);
}