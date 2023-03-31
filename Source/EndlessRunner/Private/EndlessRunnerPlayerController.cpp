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
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Started, this, &AEndlessRunnerPlayerController::OnInputJump);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Completed, this, &AEndlessRunnerPlayerController::OnInputStopJump);
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

void AEndlessRunnerPlayerController::OnInputJump()
{
	GetCharacter()->JumpMaxHoldTime = JumpHoldTime;
	GetCharacter()->Jump();
}
void AEndlessRunnerPlayerController::OnInputStopJump()
{
	GetCharacter()->StopJumping();
}

void AEndlessRunnerPlayerController::ChangeLane(bool toRight) 
{
	if (toRight && CurrentLane < 1) {
		CurrentLane++;
	} else if (!toRight && CurrentLane > -1) {
		CurrentLane--;
	} else { return; }
	
}

void AEndlessRunnerPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickLaneMovement(DeltaTime);
}

void AEndlessRunnerPlayerController::TickLaneMovement(float DeltaTime)
{
	AEndlessRunnerCharacter* ERCharacter = CastChecked<AEndlessRunnerCharacter>(GetCharacter());
	if (ERCharacter == nullptr) { return; }

	float TargetXPos = CurrentLane * LaneWidth;
	FVector CharPos = ERCharacter->GetActorLocation();
	float MoveSpeed = LaneWidth / SecondsPerLaneChange;

	if (std::abs(CharPos.X - TargetXPos) <= MoveSpeed * DeltaTime) {
		CharPos.X = TargetXPos;
	}
	else {
		int Sign = CharPos.X - TargetXPos < 0 ? 1 : -1; //Move to left or right?
		CharPos.X += DeltaTime * MoveSpeed * Sign;
	}

	ERCharacter->SetActorRelativeLocation(CharPos);
}