// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisLobbyWidget.h"
#include "LobbyGameModeBase.h"
#include "TetrisGameInstance.h"

void UTetrisLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTetrisLobbyWidget::OnStartButtonClicked);
	}

	WidthSize->SetText(FText::FromString(TEXT("10")));
	HeightSize->SetText(FText::FromString(TEXT("20")));
}

void UTetrisLobbyWidget::OnStartButtonClicked()
{
    FString WidthText = WidthSize->GetText().ToString();
    FString HeightText = HeightSize->GetText().ToString();
    int32 WidthValue = FCString::Atoi(*WidthText);
    int32 HeightValue = FCString::Atoi(*HeightText);

    UTetrisGameInstance* Inst = Cast<UTetrisGameInstance>(GetGameInstance());
    if (Inst)
    {
        Inst->BoardWidth = WidthValue;
        Inst->BoardHeight = HeightValue;
    }

    // �κ� ���� ��� ��������
    ALobbyGameModeBase* LobbyGameMode = Cast<ALobbyGameModeBase>(GetWorld()->GetAuthGameMode());
    if (LobbyGameMode)
    {
        LobbyGameMode->StartGame();
    }
}


