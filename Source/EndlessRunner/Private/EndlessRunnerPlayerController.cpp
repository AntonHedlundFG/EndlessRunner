// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerPlayerController.h"
#include "EndlessRunnerCharacter.h"

void AEndlessRunnerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Hook up all input actions to their respective functions. 
	//Note that InputJump has a Started and Completed phase as we can hold down the jump
	//button for a while to jump higher.
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputRight, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputRight);
		EnhancedInputComponent->BindAction(InputLeft, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputLeft);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Started, this, &AEndlessRunnerPlayerController::OnInputJump);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Completed, this, &AEndlessRunnerPlayerController::OnInputStopJump);
		EnhancedInputComponent->BindAction(InputPause, ETriggerEvent::Started, this, &AEndlessRunnerPlayerController::OnInputPause);

		EnhancedInputComponent->BindAction(InputRightP2, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputRightP2);
		EnhancedInputComponent->BindAction(InputLeftP2, ETriggerEvent::Triggered, this, &AEndlessRunnerPlayerController::OnInputLeftP2);
		EnhancedInputComponent->BindAction(InputJumpP2, ETriggerEvent::Started, this, &AEndlessRunnerPlayerController::OnInputJumpP2);
		EnhancedInputComponent->BindAction(InputJumpP2, ETriggerEvent::Completed, this, &AEndlessRunnerPlayerController::OnInputStopJumpP2);

		//Without this, we cannot unpause using input devices
		InputPause->bTriggerWhenPaused = true;
	}
}

void AEndlessRunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	GameState = GetWorld()->GetGameState<AEndlessRunnerGameStateBase>();
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
	if (GameState->GetCurrentGameplayState() != GameplayState::Play) { return; }
	GetCharacter()->JumpMaxHoldTime = JumpHoldTime;
	GetCharacter()->Jump();
}
void AEndlessRunnerPlayerController::OnInputStopJump()
{
	GetCharacter()->StopJumping();
}

void AEndlessRunnerPlayerController::OnInputRightP2()
{
	if (GetP2Controller()) {
		GetP2Controller()->OnInputRight();
	}
}

void AEndlessRunnerPlayerController::OnInputLeftP2()
{
	if (GetP2Controller()) {
		GetP2Controller()->OnInputLeft();
	}
}

void AEndlessRunnerPlayerController::OnInputJumpP2()
{
	if (GetP2Controller()) {
		GetP2Controller()->OnInputJump();
	}
}
void AEndlessRunnerPlayerController::OnInputStopJumpP2()
{
	if (GetP2Controller()) {
		GetP2Controller()->OnInputStopJump();
	}
}

TObjectPtr<AEndlessRunnerPlayerController> AEndlessRunnerPlayerController::GetP2Controller()
{
	if (StoredP2Controller != nullptr) { return StoredP2Controller; }
	if (TObjectPtr<APlayerController> ControllerP2 = UGameplayStatics::GetPlayerController(this, 1))
	{
		StoredP2Controller = Cast<AEndlessRunnerPlayerController>(ControllerP2);
		return StoredP2Controller;
	}
	return nullptr;
}

void AEndlessRunnerPlayerController::OnInputPause()
{
	GameState->InputPause();
}

void AEndlessRunnerPlayerController::ChangeLane(bool Right)
{
	if (GameState->GetCurrentGameplayState() != GameplayState::Play) { return; }
	if (Right && CurrentLane < 1) {
		CurrentLane++;
	} else if (!Right && CurrentLane > -1) {
		CurrentLane--;
	} else { return; }
	
}

void AEndlessRunnerPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Movement functionality below only applies during the Play state
	if (GameState->GetCurrentGameplayState() != GameplayState::Play) { return; }

	//If CharacterRef does not contain a reference to the controlled Character, assign it
	if (CharacterRef == nullptr) {
		CharacterRef = CastChecked<AEndlessRunnerCharacter>(GetCharacter());
		if (CharacterRef == nullptr) { return; }
	}
	
	//Determine desired lane position, current character position, and movement speed.
	float TargetXPos = CurrentLane * LaneWidth;
	FVector CharPos = CharacterRef->GetActorLocation();
	float MoveSpeed = LaneWidth / SecondsPerLaneChange;

	//If we're very close to the target, reach it
	//Otherwise move toward it based on movement speed
	if (std::abs(CharPos.X - TargetXPos) <= MoveSpeed * DeltaTime) {
		CharPos.X = TargetXPos;
	} 
	else {
		int Sign = CharPos.X - TargetXPos < 0 ? 1 : -1; //Move to left or right?
		CharPos.X += DeltaTime * MoveSpeed * Sign;
	}

	//Update character position based on previous calculation.
	CharacterRef->SetActorRelativeLocation(CharPos);

}