// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Delegates/Delegate.h"
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

	//Obstacles call this when they collide with a character, 
	//regardless of invulnerability status.
	void CollideWithObstacle();

	//Can be called from the Game Mode to establish max life amount
	void SetMaxLives(int Lives);

	//Can be called from PlayerControllers when the Pause button is pressed
	void InputPause();

	//This delegate is broadcast whenever the game speed changes
	//passing along the new speed value as a float
	UPROPERTY(BlueprintAssignable)
	FOnGameSpeedChange OnGameSpeedChange;

	//Broadcast whenever the GameplayState changes
	//passing along the new state as an enum
	UPROPERTY(BlueprintAssignable)
	FOnGameplayStateChange OnGameplayStateChange;

	//Broadcast whenever a new entry is added to the high score
	UPROPERTY(BlueprintAssignable)
	FOnHighScoreChange OnHighScoreChange;

	//Broadcast whenever the game ends and the players have a high enough
	//score to place on the leaderboard, which requires a UI name input event
	UPROPERTY(BlueprintAssignable)
	FOnRequestNameInput OnRequestNameInput;

	//This is the method that should be called by the UI name input event
	//when the delegate above is broadcast.
	UFUNCTION(BlueprintCallable)
	void NameInputRequestResponse(FString Name);

	GameplayState GetCurrentGameplayState() { return CurrentGameplayState; }

	float GetSpeed() { return CurrentSpeed; }

	UPROPERTY(VisibleAnywhere)
	float InvulnerableDuration = 2.0f;

protected:

	UPROPERTY()
	GameplayState CurrentGameplayState = GameplayState::Pause;

	UPROPERTY()
	float CurrentSpeed = 2000.0f;

	//C++ class that stores high scores, w/ file loading/saving.
	HighScoreManager HighScore;

	//Print-ready format w/ linebreaks
	UFUNCTION(BlueprintCallable)
	FString GetHighScoreString() { return HighScore.GetString(); }

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentScore;
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentLives;

	//This is a timer function & handle that keeps track of invulnerability
	//Called from CollideWithObstacle(). 
	//OnOllisionTimer() does nothing right now, could be used to end
	//an invulnerability animation
	FTimerHandle CollisionTimerHandle;
	void OnCollisionTimer();

	//EndGame() runs when players run out of lives, 
	//checks if the end score places on the leaderboard, 
	//and then starts a timer to run ResetGame() after ResetGameDuration seconds.
	void EndGame();
	FTimerHandle EndGameTimerHandle;
	void ResetGame();

	UPROPERTY(VisibleAnywhere)
	float ResetGameDuration = 3.0f;

	//Used to set the speed and state of the game while also broadcasting delegates.
	void SetSpeed(float NewSpeed);
	void SetState(GameplayState NewState);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
