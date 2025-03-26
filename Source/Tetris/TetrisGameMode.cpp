// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"
#include "TetrisController.h"
#include "TetrisGameInstance.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	UTetrisGameInstance* Inst = Cast<UTetrisGameInstance>(GetGameInstance());

	
	Board = GetWorld()->SpawnActor<ATetrisBoard>(BoardBP);
	if (Inst)
	{
		Board->SetBoardSize(Inst->BoardWidth, Inst->BoardHeight);
	}
	else
	{
		Board->SetBoardSize(10, 20);
	}
	Board->GameStart();

	ATetrisController* Controller = Cast<ATetrisController>(GetWorld()->GetFirstPlayerController());
	Controller->SetBoard(Board);
}

void ATetrisGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
