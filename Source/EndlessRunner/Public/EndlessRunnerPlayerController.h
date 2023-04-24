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

	void OnInputRight();
	void OnInputLeft();
	void OnInputJump();
	void OnInputStopJump();
	void OnInputPause();
	void ChangeLane(bool toRight);	
	void TickLaneMovement(float DeltaTime);
};
