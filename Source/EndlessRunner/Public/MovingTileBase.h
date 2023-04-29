// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectPtr.h"
#include "MovingTileBase.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMovingTileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingTileBase();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> RootMeshComponent;

	UFUNCTION()
	void GetBoxCenterAndExtents(FVector& Center, FVector& Extents) const;

};
