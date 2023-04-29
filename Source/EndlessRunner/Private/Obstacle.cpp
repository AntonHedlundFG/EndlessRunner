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

	//For now, always spawns with 2 random modifiers. 
	//This can be replaced and called from the TileSpawner.
	ApplyRandomModifiers(2);
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
	// If it is, notify the GameState and destroy the obstacle.
	AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (RunnerCharacter && GameState) {
		GameState->CollideWithObstacle();
		Destroy();
	}
	
}

void AObstacle::ApplyModifiers(TArray<ObstacleModifier> Modifiers)
{
	FVector NewScale = GetActorScale();
	FVector NewPosition = GetActorLocation();

	if (Modifiers.Contains(ObstacleModifier::Wide))
	{
		NewScale.X = WideModifier;
	}
	if (Modifiers.Contains(ObstacleModifier::Deep))
	{
		NewScale.Y = DeepModifier;
	}
	if (Modifiers.Contains(ObstacleModifier::Tall)) 
	{
		NewScale.Z = TallModifier;
	}
	if (Modifiers.Contains(ObstacleModifier::Flying))
	{
		NewPosition.Z += FMath::RandRange(FlyingMinHeight, FlyingMaxHeight);
	}
	SetActorScale3D(NewScale);
	SetActorLocation(NewPosition);
}

void AObstacle::ApplyRandomModifiers(int NumberOfMods)
{
	TArray<ObstacleModifier> Mods;
	NumberOfMods = FMath::Min(NumberOfMods, (int)ObstacleModifier::Num);

	//Somewhat inefficient since it can "try" to add the same modifiers over and over again
	//But since it's unlikely that we will want more than 1-2 modifiers at a time
	//This will not be a problem.
	for (int i = 0; i < NumberOfMods;)
	{
		ObstacleModifier RandomMod = (ObstacleModifier)(std::rand() % (int)ObstacleModifier::Num);
		if (!Mods.Contains(RandomMod)) {
			Mods.Add(RandomMod);
			i++;
		}
	}
	ApplyModifiers(Mods);
}