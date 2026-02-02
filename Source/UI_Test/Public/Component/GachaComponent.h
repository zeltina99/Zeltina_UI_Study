// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Framework/Data/GachaStructs.h"
#include "UI/Summon/SummonPopupWidget.h"
#include "GachaComponent.generated.h"


// 델리게이트: 가챠 결과가 나왔을 때 UI에 알려줌
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGachaFinished, const TArray<FGachaResult>&, Results);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UI_TEST_API UGachaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region 초기화
	UGachaComponent();

protected:
	virtual void BeginPlay() override;
#pragma endregion

public:
#pragma region Public API
	/**
	 * @brief 가챠 소환을 요청한다.
	 * @param SummonCount 소환 횟수 (1 or 10)
	 * @param GachaType 가챠 종류 (캐릭터 or 무기)
	 */
	UFUNCTION(BlueprintCallable, Category = "Gacha")
	void RequestSummon(int32 SummonCount, EGachaType GachaType);

	/**
	 * @brief 현재 천장 카운트를 반환한다 (UI 표시용).
	 * @return 현재 누적된 소환 횟수.
	 */
	UFUNCTION(BlueprintPure, Category = "Gacha")
	int32 GetCurrentPityCount() const { return CurrentPityCount; }
#pragma endregion

protected:
#pragma region Internal Logic
	/**
	 * @brief 단일 가챠 결과를 계산한다.
	 * @param GachaType 가챠 종류
	 * @return 계산된 결과 구조체
	 */
	FGachaResult CalculateOneSummon(EGachaType GachaType);

	/**
	 * @brief 데이터 테이블에서 랜덤하게 아이템 ID를 가져온다.
	 * @param TargetRarity 목표 등급
	 * @param GachaType 가챠 종류
	 * @return 아이템 RowName
	 */
	FName PickRandomItemID(EItemRarity TargetRarity, EGachaType GachaType);
#pragma endregion

public:
#pragma region Delegates
	/** @brief 가챠 완료 시 호출되는 이벤트 디스패처 */
	UPROPERTY(BlueprintAssignable, Category = "Gacha")
	FOnGachaFinished OnGachaFinished;
#pragma endregion

protected:
#pragma region Data Assets
	/** @brief 확률 테이블 (DT_GachaProb) */
	UPROPERTY(EditDefaultsOnly, Category = "Gacha|Data")
	TObjectPtr<UDataTable> ProbabilityTable = nullptr;

	/** @brief 캐릭터 목록 테이블 (DT_Character) */
	UPROPERTY(EditDefaultsOnly, Category = "Gacha|Data")
	TObjectPtr<UDataTable> CharacterPoolTable = nullptr;

	/** @brief 무기 목록 테이블 (DT_Weapon) */
	UPROPERTY(EditDefaultsOnly, Category = "Gacha|Data")
	TObjectPtr<UDataTable> WeaponPoolTable = nullptr;
#pragma endregion

private:
#pragma region Internal State
	/** @brief 전설 등급 천장 카운트 (저장 필요) */
	int32 CurrentPityCount = 0;

	/** @brief 전설 확정 기준 횟수 (테이블에서 읽어오거나 상수로 정의) */
	const int32 LEGEND_PITY_LIMIT = 50;
#pragma endregion

		
};
