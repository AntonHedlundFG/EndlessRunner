// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTileBase.h"
#include "EndlessRunnerEnums.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TileSpawner.generated.h"

class AEndlessRunnerGameStateBase;

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

	//Location for spawning new tiles
	UPROPERTY(EditAnywhere)
	FVector FixedSpawnLocation;

	//Used for CheckSpawnNewTile()
	UPROPERTY(EditAnywhere)
	float SpawnNewTileAtYPosition = -2000.0f;

	//Used for CheckDeleteOldestTile()
	UPROPERTY(EditAnywhere)
	float DeleteAtYPosition = 3000.0f;

	//Movement speed for tiles
	UPROPERTY(VisibleAnywhere)
	float TileSpeed = 100.0f;

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

private:

	//Spawns a random tiletype from TileList at FixedSpawnLocation
	void SpawnRandomTile();

	//Tick-moves each spawned tile based on TileSpeed
	void MoveSpawnedTiles(float DeltaTime);

	//Checks if the oldest tile has moved past DeleteAtYPosition and deletes it
	void CheckDeleteOldestTile();

	//Checks if the newst tile has moved past SpawnNewTileAtYPosition and spawns a new one
	void CheckSpawnNewTile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
