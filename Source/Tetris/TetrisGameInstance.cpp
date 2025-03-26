// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameInstance.h"

UTetrisGameInstance::UTetrisGameInstance()
{
	WallKickData[0] = { FVector2D(0, 0), FVector2D(-1, 0), FVector2D(-1, 1), FVector2D(0, -2), FVector2D(-1, -2) };
	WallKickData[1] = { FVector2D(0, 0), FVector2D(1, 0), FVector2D(1, -1), FVector2D(0, 2), FVector2D(1, 2) };
	WallKickData[2] = { FVector2D(0, 0),FVector2D(1, 0), FVector2D(1, 1), FVector2D(0, -2), FVector2D(1, -2) };
	WallKickData[3] = { FVector2D(0, 0),FVector2D(-1, 0), FVector2D(-1, -1), FVector2D(0, 2), FVector2D(-1, 2) };
	WallKickDataI[0] = { FVector2D(0, 0), FVector2D(-2, 0), FVector2D(1, 0), FVector2D(-2, -1), FVector2D(1, 2) };
	WallKickDataI[1] = { FVector2D(0, 0), FVector2D(-1, 0), FVector2D(2, 0), FVector2D(-1, 2), FVector2D(2, -1) };
	WallKickDataI[2] = { FVector2D(0, 0), FVector2D(2, 0), FVector2D(-1, 0), FVector2D(2, 1), FVector2D(-1, -2) };
	WallKickDataI[3] = { FVector2D(0, 0), FVector2D(1, 0), FVector2D(-2, 0), FVector2D(1, -2), FVector2D(-2, 1) };
}
