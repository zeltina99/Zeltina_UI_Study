// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyLobbyWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * @class UMyLobbyWidget
 * @brief 게임의 메인 로비 화면을 관리하는 위젯입니다.
 * @note 재화 표시(골드, 쥬얼)와 메뉴(스테이지, 상점 등)로의 이동을	담당합니다.
 */
UCLASS()
class UI_TEST_API UMyLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	/**
	 * @brief UI의 재화 텍스트를 갱신합니다.
	 * @param Gold 현재 보유 골드
	 * @param Gem 현재 보유 쥬얼
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateCurrencies(int32 Gold, int32 Gem);

private:
	// --- [Top Area : 상단 재화 및 설정] ---
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GemText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingBtn;

	// --- [Menu Area : 우측 메뉴 버튼들] ---
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ShopBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CharacterBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EquipmentBtn;

	// --- [클릭 이벤트 함수들] ---
	UFUNCTION() 
	void OnStageClicked();
	UFUNCTION() 
	void OnShopClicked();
	UFUNCTION() 
	void OnCharacterClicked();
	UFUNCTION() 
	void OnEquipmentClicked();
	UFUNCTION() 
	void OnSettingClicked();
};