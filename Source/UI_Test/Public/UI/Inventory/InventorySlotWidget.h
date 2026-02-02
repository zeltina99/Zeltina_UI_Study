// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Framework/Data/GameEnums.h"
#include "Framework/Data/InventoryStructs.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class UButton;
class UBorder;
class UTextBlock;

/**
 * @class UInventorySlotWidget
 * @brief 인벤토리 그리드 내의 단일 아이템/캐릭터 슬롯 UI입니다.
 * @details 
 * - 캐릭터 또는 아이템 데이터를 받아 아이콘, 테두리 색상, 레벨 등을 표시합니다.	
 * - 보유 여부(Owned)에 따라 잠금(Lock) 아이콘을 표시하거나 클릭 이벤트를 제어합니다.
 */
UCLASS()
class UI_TEST_API UInventorySlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 캐릭터 데이터를 기반으로 슬롯을 초기화합니다.
	 * @param ID 캐릭터의 고유 ID (RowName)
	 * @param Data 캐릭터 도감 정보 (아이콘, 등급 등)
	 * @param OwnedData 내 보유 정보 (레벨 등). 미보유 시 nullptr.
	 */
	//void InitCharacterSlot(FName ID, const FCharacterUIData& Data, const FOwnedHeroData* OwnedData);

	/**
	 * @brief 아이템(무기/방어구) 데이터를 기반으로 슬롯을 초기화합니다.
	 * @param ID 아이템의 고유 ID (RowName)
	 * @param Data 아이템 도감 정보 (아이콘, 등급 등)
	 * @param OwnedData 내 보유 정보 (강화 수치 등). 미보유 시 nullptr.
	 */
	//void InitItemSlot(FName ID, const FItemUIData& Data, const FOwnedItemData* OwnedData);

protected:
	/**
	 * @brief 위젯이 초기화될 때 호출됩니다. 버튼 이벤트를 바인딩합니다.
	 */
	virtual void NativeOnInitialized() override;


	/**
	 * @brief 리스트 아이템의 데이터가 설정될 때 호출된다 (인터페이스 구현).
	 * @details Tile View가 스크롤될 때마다 이 함수가 호출되어 UI 내용을 갈아끼운다.
	 * @param ListItemObject 전달된 데이터 객체 (UInventoryItemData)
	 */
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	/**
	 * @brief 아이템의 아이콘 이미지를 로드하고 표시합니다.
	 * 에디터 설정을 무시하고 강제로 210x340 크기의 이미지 모드로 렌더링하여
	 * 이미지가 찌그러지거나 투명해지는 문제를 방지합니다.
	 * @param Data 표시할 인벤토리 아이템 데이터
	 */
	void UpdateIcon(class UInventoryItemData* Data);

	/**
	 * @brief 등급 테두리 색상 및 레벨 텍스트 등 부가적인 정보를 갱신합니다.
	 * @param Data 표시할 인벤토리 아이템 데이터
	 */
	void UpdateVisuals(class UInventoryItemData* Data);

	/**
	 * @brief 아이템의 보유/미보유 상태에 따라 UI 상호작용 및 시각 효과를 처리합니다.
	 * 보유 중일 때는 밝게 표시하고 버튼을 활성화하며,
	 * 미보유 중일 때는 어둡게(Dimmed) 처리하고 버튼을 비활성화합니다.
	 * @param bOwned 아이템 보유 여부
	 */
	void UpdateState(bool bOwned);       

	/**
	 * @brief 등급(Enum)에 맞는 테두리 색상을 반환합니다.
	 * @param Rarity 아이템의 등급 (Common ~ Legendary)
	 * @return 해당 등급의 지정 색상 (FLinearColor)
	 */
	FLinearColor GetRarityColor(EItemRarity Rarity);

#pragma region 메인 UI 컴포넌트
	/**
	 * @brief 터치 입력을 받는 버튼 (미보유 시 비활성화됨).
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SlotBtn;

	/**
	 * @brief 아이템/캐릭터의 아이콘 이미지.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IconImage;

	/**
	 * @brief 등급(Rarity)에 따라 색상이 변하는 테두리 이미지.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> RarityBorder;

	/**
	 * @brief 미보유 시 화면을 가리는 반투명 자물쇠 오버레이. 현재는 안 씀
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LockOverlay;

	/**
	 * @brief 레벨 또는 강화 수치를 표시하는 텍스트 (+10, Lv.50).
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;
#pragma endregion

private:
	/**
	 * @brief 현재 슬롯이 담당하는 아이템의 ID.
	 */
	FName MyID;

	/**
	 * @brief 플레이어가 이 아이템을 소유하고 있는지 여부.
	 */
	bool bIsOwned = false;

	/**
	 * @brief 슬롯 버튼 클릭 시 호출되는 핸들러입니다.
	 * @details 보유 중일 때만 상세 정보 팝업 로직을 수행합니다.
	 */
	UFUNCTION()
	void OnClicked();

	
};
