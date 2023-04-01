// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTileBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TileSpawner.generated.h"

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


	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMovingTileBase>> TileList;

	UPROPERTY(EditAnywhere)
	FVector FixedSpawnLocation;

	UPROPERTY(EditAnywhere)
	float TileSpeed = 100.0f;

	TArray<AMovingTileBase*> SpawnedTiles;

	UPROPERTY(EditAnywhere)
	AMovingTileBase* StarterTile;

private:

	void SpawnRandomTile();
	void MoveSpawnedTiles(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
