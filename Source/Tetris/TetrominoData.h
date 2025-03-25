// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TetrominoData.generated.h"

USTRUCT(BlueprintType)
struct FBlockData
{
    GENERATED_BODY()

    // ��Ʈ�ι̳� �̸�
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    FName TetrominoName;

    // ����� ��� ��ǥ (������ ����)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    TArray<FVector2D> RelativeOffset;

    // ����� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
    FLinearColor BlockColor;
};

UCLASS(BlueprintType)
class UTetrominoData : public UDataAsset
{
    GENERATED_BODY()

public:
    // ��Ʈ�ι̳��� ��� ������ (�� ����� ��� ��ġ�� ����)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetromino")
    TArray<FBlockData> Blocks;
};
