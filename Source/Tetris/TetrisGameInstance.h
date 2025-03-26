// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TetrisGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API UTetrisGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTetrisGameInstance();

	int32 BoardWidth = 10;
	int32 BoardHeight = 20;
	TArray<FVector2D> WallKickData[4];
	TArray<FVector2D> WallKickDataI[4];
};
