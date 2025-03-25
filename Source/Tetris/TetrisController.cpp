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
        EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ATetrisController::MoveLeft);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATetrisController::MoveRight);
        EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &ATetrisController::MoveDown);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATetrisController::Rotate);
    }
}

void ATetrisController::MoveLeft()
{
}

void ATetrisController::MoveRight()
{
}

void ATetrisController::MoveDown()
{
}

void ATetrisController::Rotate()
{
}