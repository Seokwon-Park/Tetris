// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisLobbyWidget.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	void BeginPlay();
public:
	void StartGame();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UTetrisLobbyWidget> LobbyWidgetClass;
};
