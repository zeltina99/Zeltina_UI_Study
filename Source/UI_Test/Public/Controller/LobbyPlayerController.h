// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

// 전방 선언
class UUserWidget;
class ULobbyMainWidget;

/**
 * @class ALobbyPlayerController
 * @brief 로비 레벨 전용 플레이어 컨트롤러입니다.
 * @details 게임 시작 시(BeginPlay) 로비 UI를 생성하고 화면에 띄우며, 입력 모드를 UI 전용으로 설정합니다.
 */
UCLASS()
class UI_TEST_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	/** 
	 * @brief 생성할 로비 위젯 클래스 (에디터에서 WBP_LobbyMain을 넣어줄 빈 껍데기)
	 * @note TSubclassOf를 쓰면 에디터에서 해당 클래스와 그 자식들만 목록에 뜹니다.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LobbyWidgetClass = nullptr;

	/** @brief 실제 생성된 위젯 인스턴스 */
	UPROPERTY()
	TObjectPtr<UUserWidget> LobbyWidgetInstance = nullptr;
};
