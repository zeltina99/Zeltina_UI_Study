#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Framework/Data/GameEnums.h"
#include "Framework/Data/UnitStructs.h"

#include "InventoryStructs.generated.h"


/**
 * @brief 캐릭터 도감 표시용 데이터.
 */
USTRUCT(BlueprintType)
struct FCharacterUIData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EItemRarity Rank = EItemRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UTexture2D> FaceIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UTexture2D> BodyIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (MultiLine = true))
	FText Description;
};

/**
 * @brief R&D용 아이템 도감 데이터
 * @note FItemBaseStats + FItemBaseAssets 합친 형태
 */
USTRUCT(BlueprintType)
struct FItemUIData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EItemMainType ItemType; // 무기냐 방어구냐

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (MultiLine = true))
	FText Description;
};

// =========================================================
// 3. Logic Structs (InventoryComponent.h 에서 가져옴)
// =========================================================

/**
 * @brief 내 보유 영웅 정보.
 */
USTRUCT(BlueprintType)
struct FOwnedHeroData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HeroID; // RowName

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AwakeningLevel = 0; // 초월 단계 (별 개수 표시용)
};

/**
 * @brief 내 보유 아이템 정보.
 */
USTRUCT(BlueprintType)
struct FOwnedItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID; // RowName

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnhancementLevel = 0; // +강화 수치

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1; // 보유 개수
};