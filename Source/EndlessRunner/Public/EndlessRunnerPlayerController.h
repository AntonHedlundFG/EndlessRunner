// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EndlessRunnerGameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EndlessRunnerPlayerController.generated.h"

class AEndlessRunnerGameStateBase;

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;


protected:

	TObjectPtr<AEndlessRunnerGameStateBase> GameState;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	float LaneWidth = 500.0f;

	UPROPERTY(EditAnywhere)
	float SecondsPerLaneChange = 0.5f;

	int8 CurrentLane = 0;

	UPROPERTY(EditAnywhere)
	float JumpHoldTime = 1.0f;

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

	void OnInputRight();
	void OnInputLeft();
	void OnInputJump();
	void OnInputStopJump();
	void OnInputPause();

	void OnInputRightP2();
	void OnInputLeftP2();
	void OnInputJumpP2();
	void OnInputStopJumpP2();

	TObjectPtr<AEndlessRunnerPlayerController> GetP2Controller();
	TObjectPtr<AEndlessRunnerPlayerController> StoredP2Controller;

	void ChangeLane(bool toRight);	
	void TickLaneMovement(float DeltaTime);
};
