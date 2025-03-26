// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (PlayerController)
    {
        // 마우스 커서를 보이게 설정
        PlayerController->bShowMouseCursor = true;

        // 입력 모드를 UI 모드로 설정 (UI 클릭을 허용)
        FInputModeUIOnly InputModeData;
        PlayerController->SetInputMode(InputModeData);
    }

	UTetrisLobbyWidget* LobbyWidget = CreateWidget<UTetrisLobbyWidget>(GetWorld(), LobbyWidgetClass);
	if (LobbyWidget)
	{
		LobbyWidget->AddToViewport();
	}


}

void ALobbyGameModeBase::StartGame()
{
	UGameplayStatics::OpenLevel(this, "Tetris");
}
