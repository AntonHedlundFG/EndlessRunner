// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EndlessRunnerGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void RemoveLife();
	void SetMaxLives(int lives);

protected:
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentLives;
};
