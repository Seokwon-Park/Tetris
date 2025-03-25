// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlock.h"
#include "TetrominoData.h"
#include "TetrisBoard.generated.h"

UENUM(BlueprintType)
enum class ETetrisBoardState : uint8
{
	Waiting UMETA(DisplayName = "Waiting"),       // ��� ��
	Spawning UMETA(DisplayName = "Spawning"),     // ��� ���� ��
	Falling UMETA(DisplayName = "Falling"),       // ����� �������� ����
	Paused UMETA(DisplayName = "Paused"),         // �Ͻ� ����
	GameOver UMETA(DisplayName = "Game Over"),    // ���� ����
	Building UMETA(DisplayName = "Building")      // ��� �״� ��
};

UCLASS()
class TETRIS_API ATetrisBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBoardSize(int _Width, int _Height);

	void SpawnBlock();

	void GameStart() { State = ETetrisBoardState::Spawning; }

	void MoveLeft();
	void MoveRight();
	void UpdateLocation();
	void MoveDown();
	void Rotate();

	UPROPERTY()
	int Width;

	UPROPERTY()
	int Height;

	int X;
	int Y;

	FVector MeshSize ;

	ETetrisBoardState State = ETetrisBoardState::Waiting;

	TArray<TArray<ATetrisBlock*>> Board;

	TArray<ATetrisBlock*> CurTetromino;

	FVector Offset;

	FBlockData CurBlockData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATetrisBlock> Boundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTetrominoData* BlockDataAsset;
};
