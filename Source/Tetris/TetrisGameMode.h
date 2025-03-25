// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TetrisBoard.h"
#include "TetrominoData.h"
#include "TetrisGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	ATetrisBoard* GetTetrisBoard()
	{
		return Board;
	}

	ATetrisBoard* Board = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATetrisBoard> BoardBP;
};
