// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTileBase.h"
#include "EndlessRunnerEnums.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TileSpawner.generated.h"

class AEndlessRunnerGameStateBase;
class AObstacle;

UCLASS()
class ENDLESSRUNNER_API ATileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//A stored cast reference to the GameState
	TObjectPtr<AEndlessRunnerGameStateBase> GameState;

	//A list of all tile blueprint types. Managed in the inspector
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMovingTileBase>> TileList;

	//A reference to the Obstacle Blueprint to spawn on tiles
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObstacleReference;

	//Location for spawning new tiles
	UPROPERTY(EditAnywhere)
	FVector FixedSpawnLocation;

	//A new tile spawns when the previous one reaches this Y position.
	UPROPERTY(EditAnywhere)
	float SpawnNewTileAtYPosition = -2000.0f;

	//A tile is deleted when it reaches this Y position.
	UPROPERTY(EditAnywhere)
	float DeleteTileYPosition = 3000.0f;

	//An obstacle is deleted when it reaches this Y position.
	UPROPERTY(EditAnywhere)
	float DeleteObstacleYPosition = 500.0f;

	//When an obstacle is deleted as a result of moving past the above Y position
	//this describes the probability that another active obstacle is destroyed.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0f, ClampMax = 1.0f))
	float ObstacleDestructionProbability = 0.3f;

	//Movement speed for tiles and obstacles
	UPROPERTY(VisibleAnywhere)
	float GameSpeed = 100.0f;


	UFUNCTION()
	void SetSpeed(float NewSpeed);

	UPROPERTY(VisibleAnywhere)
	GameplayState CurrentState;

	UFUNCTION()
	void SetState(GameplayState NewState);

	//List of all currently spawned Tile Actors
	TArray<AMovingTileBase*> SpawnedTiles;

	//Reference to the already in-scene Tile Actor.
	UPROPERTY(EditAnywhere)
	TArray<AMovingTileBase*> StarterTiles;

	//List of all currently spawned Obstacles
	TArray<TObjectPtr<AActor>> SpawnedObstacles;

protected:

	//Spawns a random tiletype from TileList at FixedSpawnLocation
	void SpawnRandomTile();

	//Tick-moves each spawned tile based on TileSpeed
	void MoveSpawnedTilesAndObstacles(float DeltaTime);

	//Checks if the oldest tile and obstacle has moved past DeleteAtYPosition and deletes it
	void CheckDeleteOldestTile();
	void CheckDeleteOldestObstacle();

	//Checks if the newest tile has moved past SpawnNewTileAtYPosition and spawns a new one
	void CheckSpawnNewTile();

	//Spawns obstacles randomly on a tile. Note: Obstacle Amount is a float
	//The fractional part is used as a percentage chance to round up 
	//For example: 2.77f => 77% chance for 3, 23% chance for 2.
	void PopulateTileWithObstacles(AMovingTileBase* Tile, float ObstacleAmountFloat);

	static void GetRandomPointOnBoxSurface(FVector BoxCenter, FVector BoxExtents, FVector& ResultingPoint);

	//Ordered from lowest Y-value to highest.
	static TArray<FVector> GetRandomPointsOnBoxSurface(FVector BoxCenter, FVector BoxExtents, int Amount);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
