// Source/UI_Test/Public/Controller/StagePlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StagePlayerController.generated.h"

#pragma region 전방선언
class UInGameHUDWidget;
class UInputMappingContext;
class UInputAction;
#pragma endregion 전방선언

/**
 * @class AStagePlayerController
 * @brief 인게임(전투 스테이지) 전용 플레이어 컨트롤러.
 * @details HUD 위젯 생성, 입력 매핑(IMC), 일시정지 등의 인게임 로직을 담당한다.
 */
UCLASS()
class UI_TEST_API AStagePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AStagePlayerController();

protected:
#pragma region 초기화
	virtual void BeginPlay() override;
#pragma endregion 초기화

public:
#pragma region UI 제어
	/** @brief 인게임 HUD 위젯을 가져옵니다. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	UInGameHUDWidget* GetInGameHUD() const { return InGameHUDInstance; }

	/** @brief 일시정지 팝업을 엽니다. (HUD의 일시정지 버튼에서 호출) */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPausePopup();
#pragma endregion UI 제어

protected:
#pragma region 데이터 설정 (Data-Driven)
	/** @brief 인게임 HUD 위젯 클래스 (WBP_InGameHUD 할당) */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInGameHUDWidget> InGameHUDClass;

	/** @brief 인게임용 입력 매핑 컨텍스트 (IMC_Default) */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
#pragma endregion 데이터 설정

private:
#pragma region 내부 상태
	/** @brief 생성된 HUD 인스턴스 */
	UPROPERTY()
	TObjectPtr<UInGameHUDWidget> InGameHUDInstance;
#pragma endregion 내부 상태
};