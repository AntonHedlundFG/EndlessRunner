// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"

// Sets default values
ATileSpawner::ATileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileSpawner::SpawnRandomTile()
{
	//Set up spawn parameters and transform for the new tile
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	const FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	//Select a random tile base in the TileList
	TSubclassOf<AMovingTileBase> RandomTile = TileList[FMath::RandRange(0, TileList.Num() - 1)];

	//Spawn the new tile
	GetWorld()->SpawnActor(RandomTile, &SpawnLocation, &SpawnRotation, SpawnParameters);
}