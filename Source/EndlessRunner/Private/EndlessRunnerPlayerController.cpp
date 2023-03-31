// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerPlayerController.h"

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
	UKismetSystemLibrary::PrintString(this, FString("Right"));
}

void AEndlessRunnerPlayerController::OnInputLeft()
{
	UKismetSystemLibrary::PrintString(this, FString("Left"));
}