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
	Updating UMETA(DisplayName = "Checking"),	  // ���� ���� üũ
	Paused UMETA(DisplayName = "Paused"),         // �Ͻ� ����
	GameOver UMETA(DisplayName = "Game Over"),    // ���� ����
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
	void UpdateGhost();
	void MoveDown();
	bool CanMoveDown(int CurY);
	void Rotate();
	void ForceDown();
	void UpdateBoard();

	UPROPERTY()
	int Width;

	UPROPERTY()
	int Height;

	int X;
	int Y;
	int GhostY = 0;
	int Rotated = 0;

	float DownTimer = 0.0f;
	float DownDelay = 0.1f;

	float MoveTimer = 0.0f;
	float MoveDelay = 0.1f;

	//�࿡ ��� ���ִ���
	TArray<int32> RowCount;
	TArray<int32> RowToDestroy;

	FVector MeshSize;

	ETetrisBoardState State = ETetrisBoardState::Waiting;

	TArray<TArray<ATetrisBlock*>> Board;
	TArray<TArray<int32>> DownArray;

	TArray<ATetrisBlock*> CurTetromino;
	TArray<ATetrisBlock*> GhostBlock;

	FVector Offset;

	FBlockData CurBlockData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATetrisBlock> Boundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTetrominoData* BlockDataAsset;
};
