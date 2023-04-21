// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerEnums.generated.h"

UENUM(BlueprintType)
enum class GameplayState : uint8 {
	Stop UMETA(DisplayName = "Stop"),
	Pause UMETA(DisplayName = "Pause"),
	Play UMETA(DisplayName = "Play")
};