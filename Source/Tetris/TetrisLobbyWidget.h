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
    // ���� ���� ��ư Ŭ�� �� ȣ��Ǵ� �Լ�
    UFUNCTION(BlueprintCallable)
    void OnStartButtonClicked();

protected:
    // UI ���� ���
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    class UEditableText* WidthSize;
    UPROPERTY(meta = (BindWidget))
    class UEditableText* HeightSize;

    // ������ �ʱ�ȭ�� �� ȣ��Ǵ� �Լ�
    virtual void NativeConstruct() override;
};
