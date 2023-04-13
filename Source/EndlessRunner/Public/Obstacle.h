// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerCharacter.h"
#include "EndlessRunnerGameStateBase.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Allow actors to initialize themselves on the C++ side after all of their 
	// components have been initialized, only called during gameplay
	virtual void PostInitializeComponents() override;

	// This function is set to be called when the OnActorBeginOverlap delegate is called
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
