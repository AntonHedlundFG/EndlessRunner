// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EndlessRunnerGameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "EndlessRunnerPlayerController.generated.h"

class AEndlessRunnerGameStateBase;
class AEndlessRunnerCharacter;

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//Keeps a cast reference to the GameState
	TObjectPtr<AEndlessRunnerGameStateBase> GameState;

	//Distance between the 3 player movement lanes, assumes that the middle lane
	//is located at x = 0.
	UPROPERTY(EditAnywhere)
	float LaneWidth = 500.0f;

	//Determines sideways movement speed
	UPROPERTY(EditAnywhere)
	float SecondsPerLaneChange = 0.5f;

	//Keeps track of the current lane; middle lane is 0
	int8 CurrentLane = 0;

	//Maximum jumping hold time
	UPROPERTY(EditAnywhere)
	float JumpHoldTime = 1.0f;

#pragma region Input Context and Actions

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputRightP2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLeftP2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJumpP2;

#pragma endregion

	//Methods called by input actions
	void OnInputRight();
	void OnInputLeft();
	void OnInputJump();
	void OnInputStopJump();
	void OnInputPause();

	//Similar methods called by input actions, these are used to communicate
	//with player 2, which does not receive input from an Inputdevice
	void OnInputRightP2();
	void OnInputLeftP2();
	void OnInputJumpP2();
	void OnInputStopJumpP2();

	//Method used by PlayerController for Player 1 to find a reference
	//To Player 2. Always use GetP2Controller() as it automatically fetches
	//A reference if not already stored.
	TObjectPtr<AEndlessRunnerPlayerController> GetP2Controller();
	TObjectPtr<AEndlessRunnerPlayerController> StoredP2Controller;

	//Stores a cast reference to the controlled Character
	TObjectPtr<AEndlessRunnerCharacter> CharacterRef;

	//Changes desired lane if possible, Right if true, Left if false
	void ChangeLane(bool Right);

public:

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void SetupInputComponent() override;
};
