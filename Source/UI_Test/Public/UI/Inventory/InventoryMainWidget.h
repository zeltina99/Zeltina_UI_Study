// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMainWidget.generated.h"

/**
 * @class UInventoryMainWidget
 * @brief 인벤토리 및 도감의 메인 화면 위젯.
 * @details 상단 탭(캐릭터/장비)을 전환하며 WrapBox에 슬롯들을 동적으로 생성하여 나열한다.
 */
UCLASS()
class UI_TEST_API UInventoryMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	/**
	 * @brief 하위 슬롯 위젯이 클릭되었을 때 호출되는 함수.
	 * * 선택된 아이템의 데이터를 받아와 좌측 상세 정보 패널(DetailPanel)의 UI를 갱신합니다.
	 * * @param InData 클릭된 슬롯의 아이템 데이터 (캐릭터 또는 무기)
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateDetailInfo(class UInventoryItemData* InData);

protected:
	/**
	 * @brief 캐릭터 탭 버튼 클릭 시 호출됩니다.
	 * 인벤토리 리스트를 캐릭터 데이터로 갱신합니다.
	 */
	UFUNCTION()
	void OnCharacterTabClicked();

	/**
	 * @brief 무기 탭 버튼 클릭 시 호출됩니다.
	 * 인벤토리 리스트를 무기 데이터로 갱신합니다.
	 */
	UFUNCTION()
	void OnWeaponTabClicked();

	/**
	 * @brief 리스트(TileView)에 데이터를 채워 넣는 내부 함수.
	 * @param bIsCharacter true면 캐릭터, false면 무기 데이터를 로드합니다.
	 */
	void RefreshList(bool bIsCharacter);

protected:
	// ========================================================================
	// UI 바인딩 변수 (WBP 에디터의 위젯 이름과 정확히 일치해야 함)
	// ========================================================================

	/** @brief 우측 인벤토리 리스트를 표시하는 타일 뷰 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTileView> ContentTileView;

	/** @brief [탭] 캐릭터 리스트 보기 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> TabCharacterBtn;

	/** @brief [탭] 무기 리스트 보기 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> TabWeaponBtn;

	/** @brief [상세창] 선택된 아이템의 큰 이미지를 표시할 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> DetailImage;

	/** @brief [상세창] 선택된 아이템의 이름을 표시할 텍스트 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DetailNameText;

	/** @brief [상세창] 장착 또는 교체 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BtnEquip;

private:
	/** @brief 현재 선택된 아이템 데이터를 임시 저장 (추후 장착 로직 등에 사용) */
	UPROPERTY()
	TObjectPtr<class UInventoryItemData> SelectedItem;
};
