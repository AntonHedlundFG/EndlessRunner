// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root mesh component. Mesh is assigned in editor
	RootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Root Mesh Component"));
	SetRootComponent(RootMeshComponent);

	//No gravity or collision, obstacle only causes overlap
	RootMeshComponent->SetEnableGravity(false);
	RootMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<AEndlessRunnerGameStateBase>();
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Add BeginOverlap to this actor's overlap delegate.
	OnActorBeginOverlap.AddDynamic(this, &AObstacle::BeginOverlap);
}

void AObstacle::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check that the other collider is the player character.
	AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (RunnerCharacter && GameState) {
		GameState->RemoveLife();
	}
	
}
