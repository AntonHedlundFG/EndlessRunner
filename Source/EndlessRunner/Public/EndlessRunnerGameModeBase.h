// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HighScoreManager.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AEndlessRunnerGameStateBase;
class HighScoreManager;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;
	
	TObjectPtr<AEndlessRunnerGameStateBase> EndlessGameState;

	UPROPERTY(BlueprintReadWrite)
	int MaxLives = 3;

	HighScoreManager HighScoreManager;

private:

	void InitEndlessGameState();

};
