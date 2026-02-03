#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/InGame/SkillSlotWidget.h" // ★ UHT 인식을 위해 Include
#include "ActionControlPanel.generated.h"

#pragma region 전방선언
class UButton;
#pragma endregion 전방선언

/**
 * @class UActionControlPanel
 * @brief 우측 하단 전투 조작(공격, 스킬, 태그)을 전담하는 패널.
 */
UCLASS()
class UI_TEST_API UActionControlPanel : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 데이터 업데이트
	/**
	 * @brief 스킬 쿨타임 시각화 갱신
	 * @param SkillIndex 0:액티브, 1:궁극기
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Combat")
	void UpdateSkillCooldown(int32 SkillIndex, float CurrentTime, float MaxTime);

	/**
	 * @brief 현재 조작 중인 캐릭터에 따라 태그 버튼 상태 변경
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Combat")
	void UpdateTagButtons(int32 ActiveCharIndex);
#pragma endregion 데이터 업데이트

protected:
#pragma region UI 컴포넌트
	/** @brief 기본 공격 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttackBtn = nullptr;

	/** @brief 액티브 스킬 슬롯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillSlotWidget> SkillSlot_Active = nullptr;

	/** @brief 궁극기 스킬 슬롯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillSlotWidget> SkillSlot_Ultimate = nullptr;

	/** @brief 태그 버튼들 */
	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UButton> TagBtn_A = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UButton> TagBtn_B = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UButton> TagBtn_C = nullptr;
#pragma endregion UI 컴포넌트
};
