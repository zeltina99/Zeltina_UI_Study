#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Framework/Data/ItemStructs.h" // EItemRarity
#include "GachaStructs.generated.h"

#pragma region 가챠 데이터 구조체

/**
 * @struct FGachaResult
 * @brief 가챠 1회의 결과를 담는 데이터 구조체.
 * @details 아이템 ID, 등급, 중복 여부 등을 포함하여 연출 및 인벤토리 처리에 사용됨.
 */
USTRUCT(BlueprintType)
struct FGachaResult
{
	GENERATED_BODY()

	/** @brief 획득한 아이템/캐릭터의 ID (RowName) */
	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	FName ItemID = NAME_None;

	/** @brief 아이템 등급 */
	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	EItemRarity Rarity = EItemRarity::Common;

	/** @brief 캐릭터 여부 (false면 무기/아이템) */
	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	bool bIsCharacter = false;

	/** @brief 중복 획득 여부 (연출 시 'NEW' 배지 표시 용도) */
	UPROPERTY(BlueprintReadOnly, Category = "Gacha")
	bool bIsDuplicate = false;
};

/**
 * @struct FGachaProbabilityData
 * @brief 데이터 테이블(DT_GachaProb)용 확률 정의 구조체.
 * @details 등급별 가중치(Weight)와 천장(Pity) 기준을 설정한다.
 */
USTRUCT(BlueprintType)
struct FGachaProbabilityData : public FTableRowBase
{
	GENERATED_BODY()

	/** @brief 등급 (Common ~ Legendary) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
	EItemRarity Rarity = EItemRarity::Common;

	/** @brief 확률 가중치 (예: 1000분율 중 10 = 1%) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
	float Weight = 0.0f;

	/** * @brief 천장 발동 횟수 (0이면 천장 없음).
	 * @details 예: 50으로 설정 시, 50회 동안 해당 등급 미획득 시 확정 지급.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
	int32 PityThreshold = 0;
};

#pragma endregion