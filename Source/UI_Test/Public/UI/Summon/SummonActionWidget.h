// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SummonActionWidget.generated.h"

#pragma region 전방선언
class UButton;
class UTextBlock;
#pragma endregion 전방선언

/**
 * @brief 소환 요청 이벤트 델리게이트
 * @param Count 소환 횟수 (1 or 10)
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSummonRequest, int32, Count);

/**
 * @class USummonActionWidget
 * @brief 가챠 소환 버튼(1회/10회) 및 비용 표시를 전담하는 위젯. [SRP 준수]
 * @details
 * - 버튼 클릭 시 델리게이트(OnSummonRequest)를 통해 상위 위젯에 소환 횟수를 전달한다.
 * - 상위 위젯의 요청에 따라 소모 비용 텍스트를 갱신한다(Data-Driven View).
 */
UCLASS()
class UI_TEST_API USummonActionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
#pragma region 초기화
	/**
	 * @brief 위젯 초기화 (버튼 이벤트 바인딩 수행)
	 */
	virtual void NativeOnInitialized() override;
#pragma endregion 초기화

public:
#pragma region 공개 API
	/**
	 * @brief 소환 비용 텍스트를 갱신한다.
	 * @details 데이터 테이블 등에서 가져온 최신 가격 정보를 UI에 반영한다.
	 * @param SingleCost 1회 소환 비용
	 * @param MultiCost 10회 소환 비용
	 */
	UFUNCTION(BlueprintCallable, Category = "Summon|Action")
	void UpdateCostText(int32 SingleCost, int32 MultiCost);
#pragma endregion 공개 API

protected:
#pragma region 이벤트 핸들러
	/**
	 * @brief 1회 소환 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickSingle();

	/**
	 * @brief 10회 소환 버튼 클릭 핸들러.
	 */
	UFUNCTION()
	void OnClickMulti();
#pragma endregion 이벤트 핸들러

public:
#pragma region 델리게이트
	/** @brief 소환 요청이 발생했을 때 호출되는 이벤트 디스패처 */
	UPROPERTY(BlueprintAssignable, Category = "Summon|Events")
	FOnSummonRequest OnSummonRequest;
#pragma endregion 델리게이트

protected:
#pragma region 바인드 위젯
	/** @brief 1회 소환 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnSingleSummon = nullptr;

	/** @brief 10회 소환 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnMultiSummon = nullptr;

	/** @brief 1회 소환 비용 표시 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextSingleCost = nullptr;

	/** @brief 10회 소환 비용 표시 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextMultiCost = nullptr;
#pragma endregion 바인드 위젯
};
