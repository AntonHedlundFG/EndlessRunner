// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"
#include "EndlessRunnerGameStateBase.h"

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

	GameState = GetWorld()->GetGameState<AEndlessRunnerGameStateBase>();
	
	if (GameState) 
	{
		SetSpeed(GameState->CurrentSpeed);
GameState->OnGameSpeedChange.AddDynamic(this, &ATileSpawner::SetSpeed);
SetState(GameState->CurrentState);
GameState->OnGameplayStateChange.AddDynamic(this, &ATileSpawner::SetState);
	}

	//Add the starter tile to SpawnedTiles array.
	//The starter tile is in the scene
	for (int i = 0; i < StarterTiles.Num(); i++)
	{
		SpawnedTiles.Add(StarterTiles[i]);
	}

	SpawnRandomTile();
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState != GameplayState::Play) { return; }
	MoveSpawnedTilesAndObstacles(DeltaTime);
	CheckDeleteOldestTile();
	CheckDeleteOldestObstacle();
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
	TObjectPtr<AActor> SpawnedActor = GetWorld()->SpawnActor(RandomTile, &SpawnLocation, &SpawnRotation, SpawnParameters);
	TObjectPtr<AMovingTileBase> SpawnedTile = CastChecked<AMovingTileBase>(SpawnedActor);

	//Populate with obstacles (REPLACE 2 WITH DIFFICULTY LOGIC)
	PopulateTileWithObstacles(SpawnedTile, 2.75f);

	//Add the tile to the SpawnedTiles array
	SpawnedTiles.Add(SpawnedTile);

}

void ATileSpawner::MoveSpawnedTilesAndObstacles(float DeltaTime)
{
	for (int i = 0; i < SpawnedTiles.Num(); i++)
	{
		FVector NewPosition = SpawnedTiles[i]->GetActorLocation();
		NewPosition.Y += DeltaTime * GameSpeed;
		SpawnedTiles[i]->SetActorLocation(NewPosition);
	}
	for (int i = 0; i < SpawnedObstacles.Num(); i++)
	{
		FVector NewPosition = SpawnedObstacles[i]->GetActorLocation();
		NewPosition.Y += DeltaTime * GameSpeed;
		SpawnedObstacles[i]->SetActorLocation(NewPosition);
	}

}
void ATileSpawner::CheckDeleteOldestTile()
{
	if (SpawnedTiles.Num() == 0) { return; }

	AActor* OldestTile = SpawnedTiles[0];
	if (OldestTile->GetActorLocation().Y >= DeleteTileYPosition)
	{
		SpawnedTiles.RemoveAt(0);
		GetWorld()->DestroyActor(OldestTile);
	}
}
void ATileSpawner::CheckDeleteOldestObstacle()
{
	if (SpawnedObstacles.Num() == 0) { return; }

	AActor* OldestObstacle = SpawnedObstacles[0];
	if (OldestObstacle->GetActorLocation().Y >= DeleteObstacleYPosition)
	{
		SpawnedObstacles.RemoveAt(0);
		GetWorld()->DestroyActor(OldestObstacle);
		
		float RandomValue = (float)rand() / RAND_MAX;
		if (RandomValue < ObstacleDestructionProbability && SpawnedObstacles.Num() > 0) 
		{
			int RandomIndex = rand() % SpawnedObstacles.Num();
			TObjectPtr<AActor> RandomObstacle = SpawnedObstacles[RandomIndex];
			SpawnedObstacles.RemoveAt(RandomIndex);
			GetWorld()->DestroyActor(RandomObstacle);
		}
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

void ATileSpawner::SetSpeed(float NewSpeed)
{
	GameSpeed = NewSpeed;
}
void ATileSpawner::SetState(GameplayState NewState)
{
	CurrentState = NewState;
}

void ATileSpawner::PopulateTileWithObstacles(AMovingTileBase* Tile, float ObstacleAmountFloat)
{
	//Cast ObstacleAmountFloat from float to int.
	//Treats the decimal remainder of the float as a percentage chance to round up instead of down.
	float Whole, Fraction;
	Fraction = std::modf(ObstacleAmountFloat, &Whole);
	int ObstacleAmount = static_cast<int>(Whole);
	float RandomValue = (float)rand() / RAND_MAX;
	if (RandomValue < Fraction) { ObstacleAmount++; }

	//Get an array of random points on the surface of the tile, using its box volume information
	FVector Center, Extents;
	Tile->GetBoxCenterAndExtents(Center, Extents);
	TArray<FVector> SurfacePoints = GetRandomPointsOnBoxSurface(Center, Extents, ObstacleAmount);

	for (int i = 0; i < SurfacePoints.Num(); i++)
	{
		//Set up spawn parameters and transform for the new obstacle
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		const FVector SpawnLocation = SurfacePoints[i];
		const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

		//Spawn the new obstacle
		TObjectPtr<AActor> SpawnedObstacle = GetWorld()->SpawnActor(ObstacleReference, &SpawnLocation, &SpawnRotation, SpawnParameters);
		SpawnedObstacles.Add(SpawnedObstacle);
	}
}

void ATileSpawner::GetRandomPointOnBoxSurface(FVector BoxCenter, FVector BoxExtents, FVector& ResultingPoint)
{
	ResultingPoint.X = FMath::RandRange(BoxCenter.X - BoxExtents.X, BoxCenter.X + BoxExtents.X);
	ResultingPoint.Y = FMath::RandRange(BoxCenter.Y - BoxExtents.Y, BoxCenter.Y + BoxExtents.Y);
	ResultingPoint.Z = BoxCenter.Z + BoxExtents.Z;
}


TArray<FVector> ATileSpawner::GetRandomPointsOnBoxSurface(FVector BoxCenter, FVector BoxExtents, int Amount)
{
	TArray<FVector> ResultingPoints;

	for (int i = 0; i < Amount; i++) 
	{
		FVector NewPoint;
		GetRandomPointOnBoxSurface(BoxCenter, BoxExtents, NewPoint);
		ResultingPoints.Add(NewPoint);
	}
	ResultingPoints.Sort([](const FVector& A, const FVector& B) {return A.Y > B.Y; });
	return ResultingPoints;
}