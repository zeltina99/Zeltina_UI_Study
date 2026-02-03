
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/InGame/SummonSlotWidget.h" // ★ UHT 인식을 위해 Include
#include "SummonControlPanel.generated.h"

#pragma region 전방선언
class UProgressBar;
class UTextBlock;
class UButton;
#pragma endregion 전방선언

/**
 * @class USummonControlPanel
 * @brief 중앙 하단 소환 시스템(슬롯 5개 + 코스트) 관리 패널.
 */
UCLASS()
class UI_TEST_API USummonControlPanel : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region 초기화
	virtual void NativeConstruct() override;
#pragma endregion 초기화

public:
#pragma region 데이터 업데이트
	/**
	 * @brief 코스트 변경 시 호출. 게이지 갱신 및 슬롯 활성/비활성 처리.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Summon")
	void UpdateCostStatus(int32 CurrentCost, int32 MaxCost);
#pragma endregion 데이터 업데이트

protected:
#pragma region UI 컴포넌트
	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<USummonSlotWidget> SummonSlot_1 = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<USummonSlotWidget> SummonSlot_2 = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<USummonSlotWidget> SummonSlot_3 = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<USummonSlotWidget> SummonSlot_4 = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<USummonSlotWidget> SummonSlot_5 = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UProgressBar> CostBar = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UTextBlock> CostText = nullptr;

	UPROPERTY(meta = (BindWidget)) 
	TObjectPtr<UButton> AutoBtn = nullptr;
#pragma endregion UI 컴포넌트

private:
#pragma region 내부 상태
	TArray<TObjectPtr<USummonSlotWidget>> SlotsArray;
#pragma endregion 내부 상태
};