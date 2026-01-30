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
	 * @brief 기본 로비 UI (WBP_Lobby).
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> MainMenuWidgetClass = nullptr;

	/**
	 * @brief 스테이지 맵 UI (WBP_StageMap) - ★ 새로 추가!.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> StageMapWidgetClass = nullptr;

	// 화면에 떠 있는 거 저장용
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidgetInstance = nullptr;
};
