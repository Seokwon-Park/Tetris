// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

void ATetrisController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (InputLocalPlayerSubsystem != nullptr)
    {
        InputLocalPlayerSubsystem->AddMappingContext(MappingContext, 0);
    }
}

void ATetrisController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Started, this, &ATetrisController::MoveLeft);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATetrisController::MoveRight);
        EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &ATetrisController::MoveDown);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATetrisController::Rotate);
    }
}

void ATetrisController::MoveLeft()
{
    if (Board != nullptr)
    {
        Board->MoveLeft();
    }
}

void ATetrisController::MoveRight()
{
    if (Board != nullptr)
    {
        Board->MoveRight();
    }
}

void ATetrisController::MoveDown()
{
    if (Board != nullptr)
    {
        Board->MoveDown();
    }
}

void ATetrisController::Rotate()
{
}