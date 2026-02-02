// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Framework/Data/GachaStructs.h"
#include "GachaComponent.generated.h"


// 델리게이트: 가챠 결과가 나왔을 때 UI에 알려줌
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGachaFinished, const TArray<FGachaResult>&, Results);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UI_TEST_API UGachaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGachaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/**
	 * @brief 소환을 요청합니다.
	 * @param SummonCount 1회 또는 10회
	 */
	UFUNCTION(BlueprintCallable, Category = "Gacha")
	void RequestSummon(int32 SummonCount);

protected:
	/** @brief 실제 확률 계산 로직 */
	FGachaResult CalculateOneSummon();

	/** @brief 천장 카운터 (저장 필요) */
	int32 CurrentPityCount = 0;

	/** @brief 전설 천장 기준 (예: 50회) */
	const int32 LegendPityLimit = 50;

	// --- 데이터 테이블 (블루프린트에서 할당) ---
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<class UDataTable> ProbabilityTable; // 확률표

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<class UDataTable> CharacterPoolTable; // 캐릭터 목록 (DT_Character)

		
};
