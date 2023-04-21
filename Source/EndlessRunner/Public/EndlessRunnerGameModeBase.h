// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
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

	UPROPERTY(EditAnywhere)
	float InvulnerableDuration = 2.0f;

private:

	void InitEndlessGameState();

};
