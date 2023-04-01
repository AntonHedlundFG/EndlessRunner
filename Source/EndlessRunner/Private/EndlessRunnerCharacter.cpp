// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerCharacter.h"


// Sets default values
AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm Component"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AEndlessRunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndlessRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEndlessRunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

