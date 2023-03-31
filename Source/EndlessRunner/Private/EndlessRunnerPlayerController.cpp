// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerPlayerController.h"
#include "EndlessRunnerCharacter.h"

AEndlessRunnerPlayerController::AEndlessRunnerPlayerController()
{
	bShowMouseCursor = true;
}

void AEndlessRunnerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputRight, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputRight);
		EnhancedInputComponent->BindAction(InputLeft, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputLeft);
	}
}

void AEndlessRunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AEndlessRunnerPlayerController::OnInputRight()
{
	ChangeLane(true);
}

void AEndlessRunnerPlayerController::OnInputLeft()
{
	ChangeLane(false);
}

void AEndlessRunnerPlayerController::ChangeLane(bool toRight) 
{
	if (toRight && CurrentLane < 1) {
		CurrentLane++;
	}
	else if (!toRight && CurrentLane > -1) {
		CurrentLane--;
	}
	
	AEndlessRunnerCharacter* ERCharacter = CastChecked<AEndlessRunnerCharacter>(GetCharacter());
	if (ERCharacter != nullptr) {
		FVector CharPos = ERCharacter->GetActorLocation();
		CharPos.X = CurrentLane * LaneWidth;
		ERCharacter->SetActorRelativeLocation(CharPos);
	}
}