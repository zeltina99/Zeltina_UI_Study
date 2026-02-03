// Source/UI_Test/Public/UI/Summon/SummonPopupWidget.h

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Framework/Data/GachaStructs.h"
#include "SummonPopupWidget.generated.h"

#pragma region 전방선언
class USummonTabWidget;
class USummonActionWidget;
class USummonBannerWidget;
class UButton;
class UTextBlock;
class UGachaComponent;
#pragma endregion 전방선언

/**
 * @class USummonPopupWidget
 * @brief 가챠 시스템의 최상위 컨테이너 위젯 (Mediator Pattern 적용).
 * @details
 * - 하위 부품 위젯(Tab, Action, Banner)을 소유하고 조율한다.
 * - 각 부품에서 발생한 이벤트를 감지하여 로직 컴포넌트(GachaComponent)에 전달한다.
 * - 컴포넌트의 데이터 변경 사항을 각 부품에 전파하여 UI를 갱신시킨다.
 */
UCLASS()
class UI_TEST_API USummonPopupWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	/**
	 * @brief 위젯 초기화 (하위 위젯 이벤트 바인딩 및 컴포넌트 캐싱).
	 */
	virtual void NativeOnInitialized() override;

	/**
	 * @brief 위젯이 화면에 보일 때 호출 (초기 상태 설정).
	 */
	virtual void NativeConstruct() override;
#pragma endregion 초기화

protected:
#pragma region 이벤트 핸들러 (중재자 역할)
	/**
	 * @brief 탭 위젯에서 탭 변경 요청이 왔을 때 호출.
	 * @param NewType 변경된 가챠 타입
	 */
	UFUNCTION()
	void HandleTabChanged(EGachaType NewType);

	/**
	 * @brief 액션 위젯에서 소환 요청이 왔을 때 호출.
	 * @param Count 요청한 소환 횟수
	 */
	UFUNCTION()
	void HandleSummonRequest(int32 Count);

	/**
	 * @brief 닫기 버튼 클릭 핸들러 (화면 전환).
	 */
	UFUNCTION()
	void OnClickClose();
#pragma endregion 이벤트 핸들러

protected:
#pragma region 화면 갱신
	/**
	 * @brief 현재 상태(CurrentTab)에 맞춰 모든 하위 위젯의 뷰를 일괄 갱신한다.
	 */
	void UpdateAllViews();

	/**
	 * @brief 현재 보유 재화 정보를 갱신한다.
	 */
	void UpdateCurrencyDisplay();
#pragma endregion 화면 갱신

protected:
#pragma region 바인드 위젯 (부품)
	/** @brief 좌측 탭 관리 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USummonTabWidget> WBP_SummonTab = nullptr;

	/** @brief 우측 하단 소환 버튼 관리 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USummonActionWidget> WBP_SummonAction = nullptr;

	/** @brief 우측 배너 및 천장 표시 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USummonBannerWidget> WBP_SummonBanner = nullptr;
#pragma endregion 바인드 위젯

protected:
#pragma region 바인드 위젯 (공통)
	/** @brief 닫기 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnClose = nullptr;

	/** @brief 현재 보유 재화 표시 (상단) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextCurrentGem = nullptr;
#pragma endregion 바인드 위젯

private:
#pragma region 내부 상태
	/** @brief 현재 선택된 가챠 탭 (기본값: 캐릭터) */
	EGachaType CurrentTab = EGachaType::Character;

	/** @brief 로직 처리를 위한 컴포넌트 캐싱 */
	UPROPERTY()
	TObjectPtr<UGachaComponent> CachedGachaComp = nullptr;
#pragma endregion 내부 상태
};