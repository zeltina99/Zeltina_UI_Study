// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotWidget.generated.h"

#pragma region 전방선언
class UImage;
class UProgressBar;
class UButton;
class UTextBlock;
class UTexture2D;
#pragma endregion 전방선언

/**
 * @class USkillSlotWidget
 * @brief 인게임 HUD에서 개별 스킬 슬롯의 UI 표시 및 상호작용을 담당하는 위젯.
 * @details
 * - SRP: 스킬 데이터(아이콘) 표시와 쿨타임(Cooldown) 시각화 로직만 담당합니다.
 * - Data-Driven: InitializeSkill 함수를 통해 외부 데이터를 주입받아 초기화합니다.
 */
UCLASS()
class UI_TEST_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/**
	 * @brief 스킬 슬롯을 데이터 기반으로 초기화합니다.
	 * @param IconTexture 스킬 아이콘 텍스처 (nullptr 허용)
	 * @param InMaxCooldown 스킬의 전체 쿨타임 (초)
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Skill")
	void InitializeSkill(UTexture2D* IconTexture, float InMaxCooldown);
#pragma endregion 초기화

public:
#pragma region 동작 제어
	/**
	 * @brief 쿨타임을 시작합니다. (스킬 사용 직후 호출)
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Skill")
	void StartCooldown();

	/**
	 * @brief 버튼의 활성/비활성 상태를 설정합니다. (마나 부족, 침묵 상태 등)
	 * @param bIsEnable true면 활성, false면 비활성
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Skill")
	void SetSlotEnabled(bool bIsEnable);
#pragma endregion 동작 제어

private:
#pragma region 내부 로직
	/** @brief Tick에서 호출되어 쿨타임 바와 텍스트를 갱신합니다. */
	void UpdateCooldownVisual(float DeltaTime);

	/** @brief 버튼 클릭 이벤트 핸들러 */
	UFUNCTION()
	void OnSkillButtonClicked();
#pragma endregion 내부 로직

public:
#pragma region 델리게이트
	// (필요 시 추가) 외부로 클릭 이벤트를 알리기 위한 델리게이트
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillSlotClicked);
	// UPROPERTY(BlueprintAssignable) FOnSkillSlotClicked OnSlotClicked;
#pragma endregion 델리게이트

protected:
#pragma region UI 컴포넌트 (BindWidget)
	/** @brief 스킬 아이콘 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IconImage = nullptr;

	/** @brief 쿨타임 진행바 (아이콘 위에 오버레이) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> CooldownBar = nullptr;

	/** @brief 남은 쿨타임 초 표시 텍스트 (옵션) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownText = nullptr;

	/** @brief 사용자 입력을 받는 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SkillBtn = nullptr;
#pragma endregion UI 컴포넌트

private:
#pragma region 데이터 (Encapsulation)
	/** @brief 현재 남은 쿨타임 */
	float CurrentCooldown = 0.0f;

	/** @brief 전체 쿨타임 (최대치) */
	float MaxCooldown = 1.0f;

	/** @brief 현재 쿨타임이 도는 중인가? */
	bool bIsCoolingDown = false;
#pragma endregion 데이터
};