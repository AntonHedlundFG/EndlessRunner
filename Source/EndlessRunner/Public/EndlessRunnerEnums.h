// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerEnums.generated.h"

UENUM(BlueprintType)
enum class GameplayState : uint8 {
	Stop UMETA(DisplayName = "Stop"),
	Pause UMETA(DisplayName = "Pause"),
	Play UMETA(DisplayName = "Play"),
	WaitingForName UMETA(DisplayName = "WaitingForName"),
	Num UMETA(DisplayName = "Num")
};

UENUM(BlueprintType)
enum class ObstacleModifier : uint8 {
	Tall UMETA(DisplayName = "Tall"),
	Flying UMETA(DisplayName = "Flying"),
	Wide UMETA(DisplayName = "Wide"),
	Deep UMETA(DisplayName = "Deep"),
	Num UMETA(DisplayName = "Num")
};