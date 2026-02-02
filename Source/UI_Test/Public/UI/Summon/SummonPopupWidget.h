// Source/UI_Test/Public/UI/Summon/SummonPopupWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SummonPopupWidget.generated.h"

#pragma region 전방선언
class UButton;
class UTextBlock;
class UImage;
class UGachaComponent;
#pragma endregion

/**
 * @enum EGachaType
 * @brief 현재 선택된 가챠 탭의 종류 (캐릭터 vs 무기)
 */
UENUM(BlueprintType)
enum class EGachaType : uint8
{
	Character UMETA(DisplayName = "Character"),
	Weapon    UMETA(DisplayName = "Weapon")
};

/**
 * @class USummonPopupWidget
 * @brief 가챠 시스템의 메인 UI 위젯.
 * @details
 * - 탭(캐릭터/무기) 전환 기능 제공.
 * - 보유 재화 및 소모 비용 표시.
 * - GachaComponent와 연동하여 소환 로직 수행.
 * - LobbyPlayerController를 통한 화면 네비게이션 처리.
 */
UCLASS()
class UI_TEST_API USummonPopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	/**
	 * @brief 위젯 초기화 시 호출 (이벤트 바인딩 및 컴포넌트 캐싱).
	 */
	virtual void NativeOnInitialized() override;

	/**
	 * @brief 위젯이 화면에 그려질 때 호출 (UI 상태 초기화 및 데이터 갱신).
	 */
	virtual void NativeConstruct() override;
#pragma endregion

protected:
#pragma region 이벤트 핸들러
	/**
	 * @brief 캐릭터 탭 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickTabCharacter();

	/**
	 * @brief 무기 탭 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickTabWeapon();

	/**
	 * @brief 1회 소환 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickSingleSummon();

	/**
	 * @brief 10회 소환 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickMultiSummon();

	/**
	 * @brief 닫기 버튼 클릭 핸들러 (컨트롤러에게 화면 전환 요청).
	 */
	UFUNCTION()
	void OnClickClose();
#pragma endregion

protected:
#pragma region UI 로직
	/**
	 * @brief 현재 탭 상태(CurrentTab)에 맞춰 배너, 제목, 버튼 상태를 갱신한다.
	 */
	void UpdateView();

	/**
	 * @brief 현재 보유 중인 재화(Gem)와 천장 카운트를 갱신한다.
	 */
	void UpdateCurrencyInfo();
#pragma endregion

protected:
#pragma region 바인드 위젯 - 탭
	/** @brief 캐릭터 탭 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTabCharacter = nullptr;

	/** @brief 무기 탭 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTabWeapon = nullptr;
#pragma endregion

#pragma region 바인드 위젯 - 컨텐츠
	/** @brief 픽업 배너 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImgBanner = nullptr;

	/** @brief 배너 제목 텍스트 (예: "캐릭터 픽업") */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBannerTitle = nullptr;

	/** @brief 천장 카운트 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextPityCount = nullptr;
#pragma endregion

#pragma region 바인드 위젯 - 액션
	/** @brief 1회 소환 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnSingleSummon = nullptr;

	/** @brief 10회 소환 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnMultiSummon = nullptr;

	/** @brief 1회 소환 비용 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextSingleCost = nullptr;

	/** @brief 10회 소환 비용 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextMultiCost = nullptr;
#pragma endregion

#pragma region 바인드 위젯 - 상단 팁
	/** @brief 현재 보유 재화 표시 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextCurrentGem = nullptr;

	/** @brief 닫기 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnClose = nullptr;
#pragma endregion

private:
#pragma region 내부 상태
	/** @brief 현재 보고 있는 탭 (기본값: 캐릭터) */
	EGachaType CurrentTab = EGachaType::Character;

	/** @brief 가챠 로직 컴포넌트 (캐싱) */
	UPROPERTY()
	TObjectPtr<UGachaComponent> CachedGachaComp = nullptr;

	// [Data-Driven] 추후 DataTable에서 로드할 값 (임시 상수)
	const int32 COST_SINGLE = 160;
	const int32 COST_MULTI = 1600;
#pragma endregion
};