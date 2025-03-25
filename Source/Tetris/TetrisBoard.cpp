// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBoard.h"
#include "TetrisGameMode.h"

// Sets default values
ATetrisBoard::ATetrisBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATetrisBoard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATetrisBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
	case ETetrisBoardState::Waiting:
		return;
		break;
	case ETetrisBoardState::Spawning:
		SpawnBlock();
		break;
	case ETetrisBoardState::Falling:
		MoveLeft();
		break;
	case ETetrisBoardState::Paused:
		break;
	case ETetrisBoardState::GameOver:
		break;
	case ETetrisBoardState::Building:
		break;
	default:
		break;
	}
	

}

void ATetrisBoard::SetBoardSize(int _Width, int _Height)
{
	Width = _Width;
	Height = _Height;

	Board.SetNum(Width);
	for (int32 i = 0; i < Width; ++i)
	{
		Board[i].SetNum(Height);
	}

	auto BoundMesh = Boundary->GetDefaultObject<ATetrisBlock>();
	MeshSize = BoundMesh->GetMeshSize();
	Offset = FVector(0.0f, -Width * MeshSize.X / 2, -Height * MeshSize.Z / 2);

	for (int32 i = 0; i < Height; ++i)
	{
		Board[0][i] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[0][i]->SetActorLocation(FVector(0.0f, 0.0f, MeshSize.Z*i )+Offset);

		Board[Width-1][i] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[Width-1][i]->SetActorLocation(FVector(0.0f, MeshSize.Y*(Width-1), MeshSize.Z * i)+Offset);
	}

	for (int32 i = 1; i < Width-1; ++i)
	{
		Board[i][0] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[i][0]->SetActorLocation(FVector(0.0f, MeshSize.Y * i, 0.0f)+Offset);
	}
}

void ATetrisBoard::SpawnBlock()
{
	CurTetromino.Empty();
	if (BlockDataAsset == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "BlockDataAsset is Nullptr");
		return;
	}

	CurBlockData = BlockDataAsset->Blocks[FMath::RandRange(0, BlockDataAsset->Blocks.Num() - 1)];
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, CurBlockData.TetrominoName.ToString());
	X = Width / 2;
	Y = Height - 1;

	for (int i = 0; i < CurBlockData.RelativeOffset.Num(); i++)
	{
		ATetrisBlock* Block = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		CurTetromino.Add(Block);
		Block->SetActorLocation(FVector(0.0f, MeshSize.Z * (X+ CurBlockData.RelativeOffset[i].X), MeshSize.Z *(Y+ CurBlockData.RelativeOffset[i].Y)) + Offset);
	}

	State = ETetrisBoardState::Falling;
}

void ATetrisBoard::MoveLeft()
{
	X--;
	UpdateLocation();
}

void ATetrisBoard::MoveRight()
{
	X++;
	UpdateLocation();
}


void ATetrisBoard::MoveDown()
{
	Y--;
	UpdateLocation();
}

void ATetrisBoard::UpdateLocation()
{
	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		CurTetromino[i]->SetActorLocation(FVector(0.0f, MeshSize.Z * (X + CurBlockData.RelativeOffset[i].X), MeshSize.Z * (Y + CurBlockData.RelativeOffset[i].Y)) + Offset);
	}
}