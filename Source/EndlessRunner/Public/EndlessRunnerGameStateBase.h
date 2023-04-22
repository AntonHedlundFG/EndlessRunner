// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "Delegates/Delegate.h"
#include "TileSpawner.h"
#include "HighScoreManager.h"
#include "EndlessRunnerEnums.h"
#include "EndlessRunnerGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSpeedChange, float, NewSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayStateChange, GameplayState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHighScoreChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestNameInput);

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameStateBase();

public:
	void CollideWithObstacle();
	void SetMaxLives(int Lives);

	UPROPERTY(BlueprintAssignable)
	FOnGameSpeedChange OnGameSpeedChange;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayStateChange OnGameplayStateChange;

	UPROPERTY()
	GameplayState CurrentState = GameplayState::Play;

	UPROPERTY()
	float CurrentSpeed = 2000.0f;

	UPROPERTY(VisibleAnywhere)
	float InvulnerableDuration = 2.0f;

	HighScoreManager HighScore;

	UPROPERTY(BlueprintAssignable)
	FOnHighScoreChange OnHighScoreChange;

	UFUNCTION(BlueprintCallable)
	FString GetHighScoreString() { return HighScore.GetString(); }

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentScore;

	UPROPERTY(BlueprintAssignable)
	FOnRequestNameInput OnRequestNameInput;

	UFUNCTION(BlueprintCallable)
	void NameInputRequestResponse(FString Name);

protected:
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentLives;

	FTimerHandle CollisionTimerHandle;
	void OnCollisionTimer();

	
	

	void SetSpeed(float NewSpeed);
	void SetState(GameplayState NewState);

	void EndGame();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
