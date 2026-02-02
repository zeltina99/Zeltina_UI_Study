// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMainWidget.generated.h"

class UTileView;
class UButton;
class UImage;

/**
 * @brief 스쿼드 편성 및 인벤토리 시스템의 메인 컨트롤러.
 * * 캡슐화: 파티 데이터와 상태 변수는 private으로 보호됩니다.
 * * 로직: [선택] -> [교체 요청] -> [대상 선택] -> [교체 실행]의 흐름을 관리합니다.
 */
UCLASS()
class UI_TEST_API UInventoryMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	/**
	 * @brief (Slot -> Main) 인벤토리 슬롯 클릭 시 호출.
	 * 현재 상태(단순 조회 vs 교체 대기)에 따라 다른 동작을 수행합니다.
	 * @param InData 클릭된 슬롯의 데이터
	 */
	UFUNCTION(BlueprintCallable)
	void OnInventorySlotClicked(class UInventoryItemData* InData);

protected:
	/**
	 * @brief 파티 슬롯(A, B, C) 클릭 핸들러.
	 * 
	 * @param SlotIndex 슬롯 번호
	 */
	UFUNCTION()
	void OnPartySlotClicked(int32 SlotIndex);

	/**
	 * @brief (Detail -> Main) 교체 버튼 클릭 핸들러.
	 * 
	 */
	UFUNCTION()
	void OnSwapRequestReceived();

	/**
	 * @brief 파티 슬롯 UI를 갱신합니다..
	 * 
	 */
	void RefreshPartySlots();

	/**
	 * @brief 우측 리스트 갱신.
	 * 
	 * @param bIsCharacter 캐릭터 확인
	 */
	void RefreshInventoryList(bool bIsCharacter);

	/** @brief 탭 버튼 핸들러 */
	UFUNCTION() 
	void OnCharacterTabClicked();
	UFUNCTION() 
	void OnWeaponTabClicked();

	// ★ [수정] AddDynamic을 위한 래퍼(Wrapper) 함수들 (매개변수 없는 버전)
	UFUNCTION() void OnPartySlot0_Clicked() { OnPartySlotClicked(0); }
	UFUNCTION() void OnPartySlot1_Clicked() { OnPartySlotClicked(1); }
	UFUNCTION() void OnPartySlot2_Clicked() { OnPartySlotClicked(2); }

protected:
	// --- UI 바인딩 ---
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTileView> ContentTileView;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> TabCharacterBtn;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> TabWeaponBtn;

	// 분리된 상세 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInventoryDetailWidget> WBP_DetailPanel = nullptr;

	// 파티 슬롯 버튼들 (3개)
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> PartySlot_0;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> PartySlot_1;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> PartySlot_2;

	// 파티 슬롯 이미지들
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> PartyIcon_0;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> PartyIcon_1;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> PartyIcon_2;

private:
	// --- 내부 상태 (캡슐화) ---

	/**
	 * @brief 현재 선택된 파티 슬롯 인덱스 (없으면 -1).
	 */
	int32 SelectedPartyIndex = -1;

	/**
	 * @brief 교체 모드 활성화 여부.
	 */
	bool bIsSwapping = false;

	/**
	 * @brief 파티 데이터 저장소 (크기 3 고정).
	 */
	UPROPERTY()
	TArray<class UInventoryItemData*> PartyData;
};