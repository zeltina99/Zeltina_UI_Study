// Source/UI_Test/Public/UI/Inventory/InventoryItemData.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/InventoryStructs.h" // 기존 구조체 사용
#include "InventoryItemData.generated.h"

/**
 * @class UInventoryItemData
 * @brief 타일 뷰(Tile View) 리스트 항목에 데이터를 전달하기 위한 래퍼(Wrapper) 클래스.
 * @details UMG Tile View나 List View는 UObject 타입의 객체만 관리할 수 있으므로,
 * 구조체(struct) 형태의 데이터를 이 클래스에 담아서 UI 위젯에 전달하는 역할을 한다.
 * 하나의 클래스로 캐릭터와 무기 데이터를 모두 처리하기 위해 공용으로 사용되며,
 * bIsCharacter 플래그를 통해 현재 데이터의 타입을 구분한다.
 */
UCLASS(BlueprintType)
class UI_TEST_API UInventoryItemData : public UObject
{
	GENERATED_BODY()

public:
#pragma region 캐릭터 데이터
	/**
	 * @brief 캐릭터 고유 ID (데이터 테이블의 RowName).
	 */
	FName ID;

	/**
	 * @brief 캐릭터 UI 표시 정보 (아이콘, 등급, 이름 등).
	 */
	FCharacterUIData CharacterData;

	/**
	 * @brief 보유 여부 (true: 보유 중/잠금 해제, false: 미보유/잠금).
	 */
	bool bIsOwned;

	/**
	 * @brief 캐릭터 현재 레벨.
	 */
	int32 Level;
#pragma endregion

#pragma region 무기 데이터
	/**
	 * @brief 아이템 UI 표시 정보 (아이콘, 등급, 타입 등).
	 */
	FItemUIData ItemData;

	/**
	 * @brief 무기 강화 수치 (예: +10).
	 */
	int32 EnhancementLevel;

	/**
	 * @brief 데이터 타입 구분자 (true: 캐릭터, false: 아이템/무기).
	 */
	bool bIsCharacter;
#pragma endregion

	/**
	 * @brief 이 객체를 '캐릭터' 데이터로 초기화합니다.
	 * @details bIsCharacter를 true로 설정하고, 캐릭터 표시에 필요한 데이터를 할당합니다.
	 * @param InID 캐릭터의 고유 ID (RowName).
	 * @param InData 데이터 테이블에서 가져온 캐릭터 UI 정보.
	 * @param InOwned 현재 플레이어의 보유 여부.
	 * @param InLevel 캐릭터의 레벨.
	 */
	void InitCharacter(FName InID, const FCharacterUIData& InData, bool InOwned, int32 InLevel)
	{
		ID = InID;
		CharacterData = InData;
		bIsOwned = InOwned;
		Level = InLevel;
		bIsCharacter = true;
	}

	/**
	 * @brief 이 객체를 '아이템(무기)' 데이터로 초기화합니다.
	 * @details bIsCharacter를 false로 설정하고, 아이템 표시에 필요한 데이터를 할당합니다.
	 * @param InID 아이템의 고유 ID (RowName).
	 * @param InData 데이터 테이블에서 가져온 아이템 UI 정보.
	 * @param InOwned 현재 플레이어의 보유 여부.
	 * @param InEnhance 아이템의 강화 수치.
	 */
	void InitItem(FName InID, const FItemUIData& InData, bool InOwned, int32 InEnhance)
	{
		ID = InID;
		ItemData = InData;
		bIsOwned = InOwned;
		EnhancementLevel = InEnhance;
		bIsCharacter = false;
	}
};