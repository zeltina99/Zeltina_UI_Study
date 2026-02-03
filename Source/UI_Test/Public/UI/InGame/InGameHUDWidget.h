
#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/InGame/Panel/PartyStatusPanel.h"   // ★ 패널들은 Include
#include "UI/InGame/Panel/SummonControlPanel.h" // ★ 패널들은 Include
#include "UI/InGame/Panel/ActionControlPanel.h" // ★ 패널들은 Include
#include "InGameHUDWidget.generated.h"

#pragma region 전방선언
class UTextBlock;
class UButton;
#pragma endregion 전방선언

/**
 * @class UInGameHUDWidget
 * @brief 인게임 전체 UI를 총괄. 하위 패널들에게 데이터를 분배하는 역할(Dispatcher)을 수행.
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
#pragma region 데이터 분배 (Distribute Data)
	/** @brief 타이머 및 코스트 정보 업데이트 */
	UFUNCTION(BlueprintCallable, Category = "UI|Interface")
	void UpdateGameState(float RemainTime, int32 CurrentCost, int32 MaxCost);

	/** @brief 플레이어(캐릭터) 상태 업데이트 */
	UFUNCTION(BlueprintCallable, Category = "UI|Interface")
	void UpdatePlayerStatus(int32 CharIndex, float HP, float MaxHP);
#pragma endregion 데이터 분배

protected:
#pragma region 하위 패널 (Sub-Panels)
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPartyStatusPanel> PartyPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USummonControlPanel> SummonPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActionControlPanel> ActionPanel = nullptr;
#pragma endregion 하위 패널

protected:
#pragma region 공통 요소
	/** @brief 타이머는 중앙 상단 공통 요소이므로 여기서 직접 관리 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerText = nullptr;

	/** @brief 설정 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingsBtn = nullptr;
#pragma endregion 공통 요소
};