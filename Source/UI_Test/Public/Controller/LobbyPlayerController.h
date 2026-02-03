// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

#pragma region 전방선언
class UUserWidget;
class UGachaComponent;
struct FStreamableHandle; // 비동기 로딩 핸들
#pragma endregion 전방선언

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
#pragma region 초기화
	ALobbyPlayerController();

protected:
	virtual void BeginPlay() override;
#pragma endregion 초기화

public:
#pragma region UI 네비게이션
	/**
	 * @brief 화면 전환을 요청한다. (Main, StageMap, Character, Summon)
	 * @param ScreenName 전환할 화면의 태그 이름
	 */
	UFUNCTION(BlueprintCallable, Category = "Lobby|UI")
	void ShowScreen(FName ScreenName);
#pragma endregion UI 네비게이션

protected:
#pragma region 비동기 로딩 로직 (Async Loading)
	/**
	 * @brief 기존 위젯을 내리고 새로운 위젯을 **비동기**로 로드하여 띄운다.
	 * @details LoadSynchronous 대신 RequestAsyncLoad를 사용하여 메인 스레드 블로킹을 방지한다.
	 * @param NewWidgetClass 띄울 위젯의 Soft Class Pointer
	 */
	void ChangeWidgetAsync(TSoftClassPtr<UUserWidget> NewWidgetClass);

	/**
	 * @brief 비동기 로딩이 완료되었을 때 호출되는 콜백 함수.
	 * @param LoadedWidgetClass 로드가 완료된 위젯 클래스 정보
	 */
	void OnWidgetLoaded(TSoftClassPtr<UUserWidget> LoadedWidgetClass);
#pragma endregion 비동기 로딩 로직

protected:
#pragma region 위젯 클래스 정보 (Data-Driven)
	UPROPERTY(EditDefaultsOnly, Category = "Lobby|UI")
	TSoftClassPtr<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Lobby|UI")
	TSoftClassPtr<UUserWidget> StageMapWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Lobby|UI")
	TSoftClassPtr<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Lobby|UI")
	TSoftClassPtr<UUserWidget> SummonPopupWidgetClass;
#pragma endregion 위젯 클래스 정보

public:
#pragma region 컴포넌트
	/** @brief 가챠 로직 컴포넌트 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGachaComponent> GachaComponent = nullptr;
#pragma endregion 컴포넌트

private:
#pragma region 내부 상태
	/** @brief 현재 화면에 떠 있는 위젯 인스턴스 */
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidgetInstance = nullptr;

	/** @brief 현재 진행 중인 로딩 핸들 (로딩 취소 등에 사용 가능) */
	TSharedPtr<FStreamableHandle> CurrentLoadHandle;
#pragma endregion 내부 상태
};
