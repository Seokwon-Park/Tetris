// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h"
#include "Camera/CameraActor.h"

void ATetrisController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly InputGameMode;
    SetInputMode(InputGameMode);

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
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this, &ATetrisController::Rotate);
        EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATetrisController::Zoom);
        EnhancedInputComponent->BindAction(ForceDownAction, ETriggerEvent::Started, this, &ATetrisController::ForceDown);
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
    if (Board != nullptr)
    {
        Board->Rotate();
    }
}

void ATetrisController::Zoom(const FInputActionValue& Value)
{
    float MovementInput = Value.Get<float>();
    AActor* CurrentCamera = GetViewTarget(); // 현재 카메라 액터 가져오기
    if (CurrentCamera && CurrentCamera->IsA(ACameraActor::StaticClass()))
    {
        CurrentCamera->SetActorLocation(CurrentCamera->GetActorLocation() + FVector(MovementInput * 100.0f,0.0f, 0.0f));
    }
}

void ATetrisController::ForceDown()
{
    if (Board != nullptr)
    {
        Board->ForceDown();
    }
}

