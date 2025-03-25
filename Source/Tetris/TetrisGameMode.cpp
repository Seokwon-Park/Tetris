// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Board = GetWorld()->SpawnActor<ATetrisBoard>(BoardBP);
	Board->SetBoardSize(12, 21);
	Board->GameStart();
}

void ATetrisGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
