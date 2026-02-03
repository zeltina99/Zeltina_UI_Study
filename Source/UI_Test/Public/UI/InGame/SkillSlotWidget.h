// Source/UI_Test/Public/UI/InGame/SkillSlotWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotWidget.generated.h"

#pragma region 전방선언
class UImage;
class UProgressBar;
class UTextBlock;
class UButton;
class UTexture2D;
#pragma endregion 전방선언

/**
 * @class USkillSlotWidget
 * @brief 인게임 HUD에서 개별 스킬 슬롯(아이콘, 쿨타임)을 관리하는 위젯.
 * @details
 * - SRP: 스킬 데이터 표시와 쿨타임 시각화 역할만 수행.
 * - Data-Driven: 외부에서 초기화 함수를 통해 데이터를 주입받음.
 */
UCLASS()
class UI_TEST_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화 및 설정
	/**
	 * @brief 스킬 슬롯의 데이터를 설정합니다.
	 * @param IconTexture 스킬 아이콘 이미지
	 * @param CooldownTime 전체 쿨타임 (초)
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Skill")
	void InitializeSkill(UTexture2D* IconTexture, float CooldownTime);

	/**
	 * @brief 쿨타임 타이머를 시작합니다.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Skill")
	void StartCooldown();
#pragma endregion 초기화 및 설정

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
#pragma region 내부 로직
	/** @brief 쿨타임 진행 상태 업데이트 (Tick에서 호출) */
	void UpdateCooldownVisual(float DeltaTime);
#pragma endregion 내부 로직

private:
#pragma region UI 컴포넌트 (BindWidget)
	/** @brief 스킬 아이콘 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IconImage = nullptr;

	/** @brief 쿨타임 진행바 (원형 프로그레스 바 권장) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> CooldownBar = nullptr;

	/** @brief 스킬 버튼 (터치 입력용) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SkillBtn = nullptr;
#pragma endregion UI 컴포넌트

private:
#pragma region 데이터 상태
	/** @brief 현재 남은 쿨타임 */
	float CurrentCooldown = 0.0f;

	/** @brief 전체 쿨타임 (최대치) */
	float MaxCooldown = 1.0f;

	/** @brief 쿨타임 중인지 여부 */
	bool bIsCoolingDown = false;
#pragma endregion 데이터 상태
};