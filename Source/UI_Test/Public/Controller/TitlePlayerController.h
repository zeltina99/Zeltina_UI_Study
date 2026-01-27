// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePlayerController.generated.h"

class UUserWidget;

/**
 * @class ATitlePlayerController
 * @brief 타이틀 레벨 전용 플레이어 컨트롤러입니다.
 * @details 게임 시작 시(BeginPlay) 타이틀 UI를 생성하고 화면에 띄우며, 입력 모드를 UI 전용으로 설정합니다.
 */
UCLASS()
class UI_TEST_API ATitlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> TitleWidgetClass = nullptr; // 여기에 WBP_Title 넣음
};
