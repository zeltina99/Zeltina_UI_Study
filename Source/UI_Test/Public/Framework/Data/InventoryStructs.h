#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryStructs.generated.h"

// =========================================================
// 1. Enums (GameEnums.h 에서 가져옴)
// =========================================================

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common		UMETA(DisplayName = "Common (1 Star)"),
	Uncommon	UMETA(DisplayName = "Uncommon (2 Star)"),
	Rare		UMETA(DisplayName = "Rare (3 Star)"),
	Epic		UMETA(DisplayName = "Epic (4 Star)"),
	Legendary	UMETA(DisplayName = "Legendary (5 Star)")
};

UENUM(BlueprintType)
enum class EItemMainType : uint8
{
	Weapon		UMETA(DisplayName = "Weapon"),
	Armor		UMETA(DisplayName = "Armor"),
};

// =========================================================
// 2. Structs (UnitStructs.h + ItemStructs.h 통합 변형)
// =========================================================

/** * @brief R&D용 캐릭터 도감 데이터
 * @note 실제 프로젝트의 FUnitBaseStats + FCharacterAssets를 합친 형태입니다.
 */
USTRUCT(BlueprintType)
struct FCharacterUIData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText Name; // 캐릭터 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EItemRarity Rank; // 태생 등급

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UTexture2D> FaceIcon; // 인벤토리용 아이콘

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UTexture2D> BodyIcon; // 상세 정보용 일러스트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (MultiLine = true))
	FText Description; // 배경 스토리
};

/** * @brief R&D용 아이템 도감 데이터
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

/** @brief 내 보유 영웅 정보 */
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

/** @brief 내 보유 아이템 정보 */
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