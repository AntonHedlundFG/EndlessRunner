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

	//Add the starter tile to SpawnedTiles array.
	//The starter tile is in the scene
	if (StarterTile != nullptr) { SpawnedTiles.Add(StarterTile); }
	
	SpawnRandomTile();
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveSpawnedTiles(DeltaTime);
	CheckDeleteOldestTile();
	CheckSpawnNewTile();
}

void ATileSpawner::SpawnRandomTile()
{
	//Set up spawn parameters and transform for the new tile
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	const FVector SpawnLocation = FixedSpawnLocation;
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	//Select a random tile base in the TileList
	TSubclassOf<AMovingTileBase> RandomTile = TileList[FMath::RandRange(0, TileList.Num() - 1)];

	//Spawn the new tile
	AActor* SpawnedActor = GetWorld()->SpawnActor(RandomTile, &SpawnLocation, &SpawnRotation, SpawnParameters);
	AMovingTileBase* SpawnedTile = CastChecked<AMovingTileBase>(SpawnedActor);
	
	//Add the tile to the SpawnedTiles array
	SpawnedTiles.Add(SpawnedTile);
	
}

void ATileSpawner::MoveSpawnedTiles(float DeltaTime)
{
	for (int i = 0; i < SpawnedTiles.Num(); i++)
	{
		FVector NewPosition = SpawnedTiles[i]->GetActorLocation();
		NewPosition.Y += DeltaTime * TileSpeed;
		SpawnedTiles[i]->SetActorLocation(NewPosition);
	}
}
void ATileSpawner::CheckDeleteOldestTile()
{
	if (SpawnedTiles.Num() == 0) { return; }

	AActor* OldestTile = SpawnedTiles[0];
	if (OldestTile->GetActorLocation().Y >= DeleteAtYPosition)
	{
		SpawnedTiles.RemoveAt(0);
		GetWorld()->DestroyActor(OldestTile);
	}
}
void ATileSpawner::CheckSpawnNewTile()
{
	if (SpawnedTiles.Num() == 0) { return; }

	AActor* NewestTile = SpawnedTiles[SpawnedTiles.Num() - 1];

	if (NewestTile->GetActorLocation().Y >= SpawnNewTileAtYPosition)
	{
		SpawnRandomTile();
	}
}