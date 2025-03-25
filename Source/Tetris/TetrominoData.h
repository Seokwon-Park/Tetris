// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TetrominoData.generated.h"

USTRUCT(BlueprintType)
struct FBlockData
{
    GENERATED_BODY()

    // 테트로미노 이름
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    FName TetrominoName;

    // 블록의 상대 좌표 (기준점 기준)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    TArray<FVector2D> RelativeOffset;

    // 블록의 색상
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    FLinearColor BlockColor;
};

UCLASS(BlueprintType)
class UTetrominoData : public UDataAsset
{
    GENERATED_BODY()

public:
    // 테트로미노의 블록 데이터 (각 블록은 상대 위치와 색상)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetromino")
    TArray<FBlockData> Blocks;
};
