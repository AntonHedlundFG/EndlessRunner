// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTileBase.h"

// Sets default values
AMovingTileBase::AMovingTileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Root Tile Mesh"));
	SetRootComponent(RootMeshComponent);
}

void AMovingTileBase::GetBoxCenterAndExtents(FVector& Center, FVector& Extents) const
{
	RootMeshComponent->Bounds.GetBox().GetCenterAndExtents(Center, Extents);
}

