// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AEndlessRunnerGameStateBase;
class HighScoreManager;

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;
	virtual void BeginPlay();
	
	//Max lives, shared between both players.
	UPROPERTY(BlueprintReadWrite)
	int MaxLives = 3;

	//Invulnerable duration, shared between both players after one hits an obstacle.
	UPROPERTY(EditAnywhere)
	float InvulnerableDuration = 2.0f;

};
