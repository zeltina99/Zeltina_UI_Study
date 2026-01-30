// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMainWidget.generated.h"

class UWrapBox;
class UButton;
class UInventorySlotWidget;
class UDataTable;

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
	/**
	 * @brief 슬롯 생성을 위한 위젯 클래스 (WBP_InventorySlot).
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UInventorySlotWidget> SlotClass;

	/**
	 * @brief 캐릭터 전체 데이터가 담긴 데이터 테이블.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<UDataTable> CharacterDT;

	/**
	 * @brief 아이템(무기) 전체 데이터가 담긴 데이터 테이블.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<UDataTable> WeaponDT;

	/**
	 * @brief 캐릭터 리스트를 그리드에 표시한다.
	 */
	UFUNCTION(BlueprintCallable)
	void ShowCharacterList();

	/**
	 * @brief 무기 리스트를 그리드에 표시한다.
	 */
	UFUNCTION(BlueprintCallable)
	void ShowWeaponList();

protected:
	virtual void NativeConstruct() override;

protected:

#pragma region 메인 UI 컴포넌트
	/**
	 * @brief 아이템 슬롯들이 배치될 그리드 컨테이너.
	 * @details ScrollBox 아래에 자식으로 존재해야 스크롤이 가능하다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> ContentGrid;

	/**
	 * @brief 캐릭터 탭 전환 버튼.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TabCharacterBtn;

	/**
	 * @brief 무기 탭 전환 버튼.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TabWeaponBtn;
#pragma endregion

private:
	/**
	 * @brief 캐릭터 탭 클릭 이벤트 핸들러.
	 */
	UFUNCTION()
	void OnTabCharacterClicked();

	/**
	 * @brief 무기 탭 클릭 이벤트 핸들러.
	 */
	UFUNCTION()
	void OnTabWeaponClicked();
};
