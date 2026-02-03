// Source/UI_Test/Public/UI/InGame/InGameHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h" // CommonUI 기반
#include "InGameHUDWidget.generated.h"

#pragma region 전방선언
class UProgressBar;
class UTextBlock;
class USkillSlotWidget;
class UCommonButtonBase;
#pragma endregion 전방선언

/**
 * @class UInGameHUDWidget
 * @brief 인게임 전투 화면(HUD)을 관리하는 메인 위젯.
 * @details
 * - 스테이지(1-1, 1-2 등) 진입 시 활성화된다.
 * - 캐릭터의 HP/MP 상태 변화를 반영하고 스킬 슬롯을 관리한다.
 */
UCLASS()
class UI_TEST_API UInGameHUDWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	virtual void NativeConstruct() override;
#pragma endregion 초기화

public:
#pragma region 상태 업데이트 (Data-Driven)
	/**
	 * @brief 캐릭터 체력바 업데이트
	 * @param CurrentHP 현재 체력
	 * @param MaxHP 최대 체력
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Status")
	void UpdateHealth(float CurrentHP, float MaxHP);

	/**
	 * @brief 스테이지 정보 텍스트 설정
	 * @param StageName 예: "Stage 1-1"
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Info")
	void SetStageName(FText StageName);
#pragma endregion 상태 업데이트

private:
#pragma region 이벤트 핸들러
	/** @brief 일시정지 버튼 클릭 시 호출 */
	UFUNCTION()
	void OnPauseClicked();
#pragma endregion 이벤트 핸들러

private:
#pragma region 상태바 컴포넌트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StageNameText = nullptr;
#pragma endregion 상태바 컴포넌트

private:
#pragma region 스킬 및 조작 컴포넌트
	/** @brief 일반 공격 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillSlotWidget> SkillSlot_Attack = nullptr;

	/** @brief 액티브 스킬 1번 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillSlotWidget> SkillSlot_Q = nullptr;

	/** @brief 액티브 스킬 2번 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillSlotWidget> SkillSlot_E = nullptr;

	/** @brief 일시정지 버튼 (CommonButton 권장) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PauseBtn = nullptr;
#pragma endregion 스킬 및 조작 컴포넌트
};