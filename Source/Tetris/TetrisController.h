// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TetrisBoard.h"
#include "InputMappingContext.h"

#include "TetrisController.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisController : public APlayerController
{
	GENERATED_BODY()
protected:
    void BeginPlay();
public:
    void SetupInputComponent();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Rotate();
    void Zoom(const FInputActionValue& Value);
    void ForceDown();

    
    void SetBoard(ATetrisBoard* _Board)
    {
        Board = _Board;
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveLeftAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveRightAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveDownAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* RotateAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* ZoomAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* ForceDownAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* MappingContext = nullptr;

    ATetrisBoard* Board;

};
