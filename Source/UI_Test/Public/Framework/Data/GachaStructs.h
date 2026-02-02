#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryStructs.h" // EItemRarity 사용을 위해
#include "GachaStructs.generated.h"

/**
 * @brief 가챠 결과 하나를 담는 구조체
 */
USTRUCT(BlueprintType)
struct FGachaResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	FName ItemID;

	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	EItemRarity Rarity;

	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	bool bIsCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	bool bIsDuplicate; // 중복 여부 (조각 변환용)

	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	int32 FragmentAmount; // 중복 시 획득한 조각 개수
};

/**
 * @brief 가챠 확률 테이블 (Data Table용)
 * 등급별 확률 가중치를 정의합니다.
 */
USTRUCT(BlueprintType)
struct FGachaProbabilityData : public FTableRowBase
{
	GENERATED_BODY()

	/** @brief 등급 (Common, Rare, Epic, Legendary) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Probability")
	EItemRarity Rarity;

	/** @brief 확률 가중치 (예: Common=70, Rare=25, Epic=4, Legend=1) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Probability")
	float Weight;

	/** @brief 해당 등급 천장 카운트 (이 횟수 도달 시 확정, 0이면 없음) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Probability")
	int32 PityThreshold;
};