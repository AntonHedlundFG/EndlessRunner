// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerCharacter.h"
#include "EndlessRunnerGameStateBase.h"
#include "EndlessRunnerEnums.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Obstacle.generated.h"

class AEndlessRunnerGameStateBase;

UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();


protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RootMeshComponent;

	//Reference to GameState, initialized in BeginPlay().
	TObjectPtr<AEndlessRunnerGameStateBase> GameState;

	//These are variables for various ObstacleModifier effects, applied in
	//ApplyModifiers() & ApplyRandomModifiers()
	UPROPERTY(EditAnywhere)
	float WideModifier = 3.0f;
	UPROPERTY(EditAnywhere)
	float DeepModifier = 3.0f;
	UPROPERTY(EditAnywhere)
	float TallModifier = 3.0f;
	UPROPERTY(EditAnywhere)
	float FlyingMinHeight = 50.0f;
	UPROPERTY(EditAnywhere)
	float FlyingMaxHeight = 150.0f;

public:
	// This function is set to be called when the OnActorBeginOverlap delegate is called
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//Customize the shape & location of the obstacle
	void ApplyModifiers(TArray<ObstacleModifier> Modifiers);
	void ApplyRandomModifiers(int NumberOfMods);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Allow actors to initialize themselves on the C++ side after all of their 
	// components have been initialized, only called during gameplay
	virtual void PostInitializeComponents() override;

};
