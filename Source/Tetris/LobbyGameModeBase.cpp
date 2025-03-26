// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (PlayerController)
    {
        // ���콺 Ŀ���� ���̰� ����
        PlayerController->bShowMouseCursor = true;

        // �Է� ��带 UI ���� ���� (UI Ŭ���� ���)
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
