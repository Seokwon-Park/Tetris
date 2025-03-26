// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "TetrisLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API UTetrisLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // 게임 시작 버튼 클릭 시 호출되는 함수
    UFUNCTION(BlueprintCallable)
    void OnStartButtonClicked();

protected:
    // UI 구성 요소
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    class UEditableText* WidthSize;
    UPROPERTY(meta = (BindWidget))
    class UEditableText* HeightSize;

    // 위젯이 초기화될 때 호출되는 함수
    virtual void NativeConstruct() override;
};
