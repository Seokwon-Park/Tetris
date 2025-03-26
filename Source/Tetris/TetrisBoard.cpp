// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBoard.h"
#include "TetrisGameMode.h"
#include "TetrisGameInstance.h"

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

	DownTimer += DeltaTime;
	MoveTimer += DeltaTime;

	switch (State)
	{
	case ETetrisBoardState::Waiting:
		return;
		break;
	case ETetrisBoardState::Spawning:
		SpawnBlock();
		break;
	case ETetrisBoardState::Falling:
		break;
	case ETetrisBoardState::Updating:
		UpdateBoard();
		break;
	case ETetrisBoardState::Paused:
		break;
	case ETetrisBoardState::GameOver:
		break;
		break;
	default:
		break;
	}


}

void ATetrisBoard::SetBoardSize(int _Width, int _Height)
{
	//테두리 크기
	Width = _Width + 2;
	Height = _Height + 1;

	Board.SetNum(Width);
	DownArray.SetNum(Width);
	for (int32 i = 0; i < Width; ++i)
	{
		Board[i].SetNum(Height);
		DownArray[i].SetNum(Height);
	}

	RowCount.Init(0, Height);

	auto BoundMesh = Boundary->GetDefaultObject<ATetrisBlock>();
	MeshSize = BoundMesh->GetMeshSize();
	Offset = FVector(0.0f, -Width * MeshSize.X / 2, -Height * MeshSize.Z / 2);

	for (int32 i = 0; i < Height; ++i)
	{
		Board[0][i] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[0][i]->SetActorLocation(FVector(0.0f, 0.0f, MeshSize.Z * i) + Offset);

		Board[Width - 1][i] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[Width - 1][i]->SetActorLocation(FVector(0.0f, MeshSize.Y * (Width - 1), MeshSize.Z * i) + Offset);
	}

	for (int32 i = 1; i < Width - 1; ++i)
	{
		Board[i][0] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Board[i][0]->SetActorLocation(FVector(0.0f, MeshSize.Y * i, 0.0f) + Offset);
	}

	GhostBlock.SetNum(4);
	for (int i = 0; i < GhostBlock.Num(); i++)
	{
		GhostBlock[i] = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		GhostBlock[i]->SetColor(FLinearColor::White);
	}
}

void ATetrisBoard::SpawnBlock()
{
	CurTetromino.Empty();
	Rotated = 0;
	if (BlockDataAsset == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "BlockDataAsset is Nullptr");
		return;
	}

	CurBlockData = BlockDataAsset->Blocks[FMath::RandRange(0, BlockDataAsset->Blocks.Num() - 1)];
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, CurBlockData.TetrominoName.ToString());
	X = Width / 2;
	Y = Height - 1;

	if (Board[X][Y] != nullptr)
	{
		State = ETetrisBoardState::GameOver;
		return;
	}

	for (int i = 0; i < CurBlockData.RelativeOffset.Num(); i++)
	{
		ATetrisBlock* Block = GetWorld()->SpawnActor<ATetrisBlock>(Boundary);
		Block->SetColor(CurBlockData.BlockColor);
		CurTetromino.Add(Block);
		Block->SetActorLocation(FVector(0.0f, MeshSize.Z * (X + CurBlockData.RelativeOffset[i].X), MeshSize.Z * (Y + CurBlockData.RelativeOffset[i].Y)) + Offset);
	}

	UpdateGhost();
	State = ETetrisBoardState::Falling;
}

void ATetrisBoard::MoveLeft()
{
	if (State != ETetrisBoardState::Falling) return;
	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		if (X + CurBlockData.RelativeOffset[i].X - 1 < 1)
			return;
	}
	if (MoveTimer > MoveDelay)
	{
		X--;
		UpdateLocation();
		MoveTimer = 0.0f;
	}
}

void ATetrisBoard::MoveRight()
{
	if (State != ETetrisBoardState::Falling) return;
	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		if (X + CurBlockData.RelativeOffset[i].X + 1 >= Width - 1)
			return;
	}
	if (MoveTimer > MoveDelay)
	{
		X++;
		UpdateLocation();
		MoveTimer = 0.0f;
	}
}


void ATetrisBoard::MoveDown()
{
	if (State != ETetrisBoardState::Falling) return;
	if (CanMoveDown(Y))
	{
		if (DownTimer > DownDelay)
		{
			Y--;
			UpdateLocation();
			DownTimer = 0.0f;
		}
		if (!CanMoveDown(Y))
		{
			for (int i = 0; i < CurTetromino.Num(); i++)
			{
				int BlockX = X + CurBlockData.RelativeOffset[i].X;
				int BlockY = Y + CurBlockData.RelativeOffset[i].Y;
				Board[BlockX][BlockY] = CurTetromino[i];
				RowCount[BlockY]++;
				if (RowCount[BlockY] == Width - 2)
				{
					RowToDestroy.Add(BlockY);
				}
			}
			if (RowToDestroy.IsEmpty())
			{
				State = ETetrisBoardState::Spawning;
			}
			else
			{
				State = ETetrisBoardState::Updating;
			}
		}
	}
}

bool ATetrisBoard::CanMoveDown(int CurY)
{

	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		int BlockX = X + CurBlockData.RelativeOffset[i].X;
		int BlockY = CurY + CurBlockData.RelativeOffset[i].Y;
		if (BlockY - 1 >= Height)continue;
		if (BlockY - 1 == 0 || Board[BlockX][BlockY - 1] != nullptr)
		{
			return false;
		}
	}
	return true;
}

void ATetrisBoard::Rotate()
{
	if (State != ETetrisBoardState::Falling) return;
	TArray<FVector2D> Before = CurBlockData.RelativeOffset;

	for (int i = 0; i < CurBlockData.RelativeOffset.Num(); i++)
	{
		CurBlockData.RelativeOffset[i].X = Before[i].Y;
		CurBlockData.RelativeOffset[i].Y = -Before[i].X;
	}

	UTetrisGameInstance* Inst = Cast<UTetrisGameInstance>(GetGameInstance());
	TArray<FVector2D> TestCase;
	if (CurBlockData.TetrominoName == "I")
	{
		TestCase = Inst->WallKickDataI[(Rotated + 1) %4];
	}
	else
	{
		TestCase = Inst->WallKickData[(Rotated + 1) % 4];
	}

	bool Result = false;
	//모든 WallKickCase에 대해서 조사
	for (int CaseIx = 0; CaseIx < TestCase.Num(); CaseIx++)
	{
		bool CanRotate = true;
		for (int i = 0; i < CurTetromino.Num(); i++)
		{
			//회전된 데이터를 기반으로 계산
			int BlockX = X + CurBlockData.RelativeOffset[i].X + TestCase[CaseIx].X;
			int BlockY = Y + CurBlockData.RelativeOffset[i].Y + TestCase[CaseIx].Y;

			if (BlockX <= 0 || BlockX >= Width - 1 || BlockY <= 0 || BlockY >= Height || Board[BlockX][BlockY] != nullptr)
			{
				CanRotate = false;
				break;
			}
		}
		if (CanRotate)
		{
			X += TestCase[CaseIx].X;
			Y += TestCase[CaseIx].Y;
			Result = true;
			break;
		}
	}

	if (Result == false)
	{
		CurBlockData.RelativeOffset = Before;
	}
	else
	{
		Rotated = (Rotated + 1) % 4;
		UpdateLocation();
	}
}

void ATetrisBoard::ForceDown()
{
	if (State != ETetrisBoardState::Falling) return;
	Y = GhostY;
	UpdateLocation();
	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		int BlockX = X + CurBlockData.RelativeOffset[i].X;
		int BlockY = Y + CurBlockData.RelativeOffset[i].Y;
		Board[BlockX][BlockY] = CurTetromino[i];
		RowCount[BlockY]++;
		if (RowCount[BlockY] == Width - 2)
		{
			RowToDestroy.Add(BlockY);
		}
	}
	if (RowToDestroy.IsEmpty())
	{
		State = ETetrisBoardState::Spawning;
	}
	else
	{
		State = ETetrisBoardState::Updating;
	}
}

void ATetrisBoard::UpdateBoard()
{

	for (int RowNum : RowToDestroy)
	{
		for (int i = 1; i < Width - 1; i++)
		{
			if (Board[i][RowNum] != nullptr)
			{
				Board[i][RowNum]->Destroy();
				Board[i][RowNum] = nullptr;
			}
			DownArray[i][RowNum] = 0;
			//삭제된 Row보다 위에 있는 녀석들이 내려와야 하니까 몇칸 내려와야 하는지 저장
			for (int j = RowNum + 1; j < Height; j++)
			{
				DownArray[i][j]++;
			}
		}
		RowCount[RowNum] = 0;
	}

	for (int y = 1; y < Height; y++)
	{
		for (int x = 1; x < Width - 1; x++)
		{
			if (Board[x][y] != nullptr && DownArray[x][y] != 0)
			{
				RowCount[y]--;
				RowCount[y - DownArray[x][y]]++;
				Board[x][y]->SetActorLocation(FVector(0.0f, MeshSize.X * x, MeshSize.Z * (y - DownArray[x][y])) + Offset);
				Board[x][y - DownArray[x][y]] = Board[x][y];
				Board[x][y] = nullptr;
			}
		}
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			DownArray[x][y] = 0;
		}
	}

	RowToDestroy.Empty();
	State = ETetrisBoardState::Spawning;
}

void ATetrisBoard::UpdateLocation()
{
	for (int i = 0; i < CurTetromino.Num(); i++)
	{
		CurTetromino[i]->SetActorLocation(FVector(0.0f, MeshSize.Z * (X + CurBlockData.RelativeOffset[i].X), MeshSize.Z * (Y + CurBlockData.RelativeOffset[i].Y)) + Offset);
	}
	UpdateGhost();
}

void ATetrisBoard::UpdateGhost()
{
	GhostY = Y;
	while(CanMoveDown(GhostY))
	{
		GhostY--;
	}

	for (int i = 0; i < GhostBlock.Num(); i++)
	{
		GhostBlock[i]->SetActorLocation(FVector(0.0f, MeshSize.Z * (X + CurBlockData.RelativeOffset[i].X), MeshSize.Z * (GhostY + CurBlockData.RelativeOffset[i].Y)) + Offset);
	}
	
}
