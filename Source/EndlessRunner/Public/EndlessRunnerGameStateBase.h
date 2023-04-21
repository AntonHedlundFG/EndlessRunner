// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Delegates/Delegate.h"
#include "TileSpawner.h"
#include "EndlessRunnerEnums.h"
#include "EndlessRunnerGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSpeedChange, float, NewSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayStateChange, GameplayState, NewState);

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void RemoveLife();
	void SetMaxLives(int lives);

	//This should be removed if I can get the delegates to work properly
	void RegisterTileSpawner(TObjectPtr<ATileSpawner> Spawner);
	TObjectPtr<ATileSpawner> RegisteredTileSpawner;

	UPROPERTY(BlueprintAssignable)
	FOnGameSpeedChange OnGameSpeedChange;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayStateChange OnGameplayStateChange;

	UPROPERTY()
	GameplayState CurrentState = GameplayState::Stop;

	UPROPERTY()
	float CurrentSpeed = 100.0f;

protected:
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentLives;
};
