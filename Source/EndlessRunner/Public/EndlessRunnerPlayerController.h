// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EndlessRunnerPlayerController.generated.h"


UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEndlessRunnerPlayerController();
	
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;


protected:

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	float LaneWidth = 500.0f;

	UPROPERTY(EditAnywhere)
	float SecondsPerLaneChange = 0.5f;

	int8 CurrentLane = 0;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLeft;

	void OnInputRight();
	void OnInputLeft();
	void ChangeLane(bool toRight);	
};
