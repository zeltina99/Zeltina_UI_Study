// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

// 전방 선언
class UUserWidget;
class UGachaComponent;
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

public:
	ALobbyPlayerController();

public:
	/**
	 * @brief 지정된 이름의 화면으로 UI를 교체한다.
	 * @details 기존에 띄워진 위젯을 제거하고, 요청된 이름에 해당하는 새 위젯을 로드하여 띄운다.
	 * @param ScreenName 전환할 화면의 식별자 (예: "Main", "StageMap", "Formation", "Summon").
	 */
	UFUNCTION(BlueprintCallable)
	void ShowScreen(FName ScreenName);

protected:
	virtual void BeginPlay() override;

private:
	/**
	 * @brief 기본 로비 UI (WBP_Lobby).
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> MainMenuWidgetClass = nullptr;

	/**
	 * @brief 스테이지 맵 UI (WBP_StageMap)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> StageMapWidgetClass = nullptr;

	/**
	 * @brief 편성(인벤토리) 및 도감 위젯 클래스.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> InventoryWidgetClass = nullptr;

	/**
	 * @brief 가챠 소환 팝업 위젯 클래스.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> SummonPopupWidgetClass = nullptr;

	/**
	 * @brief 현재 화면에 띄워져 있는 위젯 인스턴스 (관리용).
	 */
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidgetInstance = nullptr;

	/**
	 * @brief 실제 위젯 교체 로직을 수행하는 내부 함수.
	 * @details 동기 로드(LoadSynchronous)를 통해 에셋을 로드하고, 뷰포트에 추가한다.
	 * @param NewWidgetClass 교체할 위젯의 Soft Class Pointer.
	 */
	void ChangeWidget(TSoftClassPtr<UUserWidget> NewWidgetClass);

public:
	/** @brief 가챠 로직을 담당하는 컴포넌트 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGachaComponent> GachaComponent = nullptr;
};
