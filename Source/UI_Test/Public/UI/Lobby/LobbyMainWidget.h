// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LobbyMainWidget.generated.h"

// 전방 선언
class ULobbyTopBarWidget;
class ULobbyMenuWidget;

/**
 * @class ULobbyMainWidget
 * @brief 게임의 메인 로비 화면 전체를 관장하는 최상위 위젯입니다.
 * @details TopBar와 MainMenu 위젯을 포함하며, 데이터 갱신 및 화면 전환 로직을 담당합니다.
 */
UCLASS()
class UI_TEST_API ULobbyMainWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	/**
	 * @brief 로비 UI 전체 데이터를 최신 상태로 갱신합니다.
	 * @note 보통 GameInstance나 PlayerState에서 데이터를 가져와 호출합니다.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Lobby")
	void RefreshLobby();

private:
	/** @brief 상단 재화 바 위젯 */	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<ULobbyTopBarWidget> WBP_TopBar = nullptr;

	/** @brief 우측 메뉴 버튼 그룹 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<ULobbyMenuWidget> WBP_MainMenu = nullptr;

	/**
	 * @brief 하위 메뉴 위젯에서 버튼이 클릭되었을 때 호출되는 콜백 함수입니다.
	 * @param MenuName 선택된 메뉴의 식별자
	 */
	UFUNCTION()
	void HandleMenuSelection(FName MenuName);
};
