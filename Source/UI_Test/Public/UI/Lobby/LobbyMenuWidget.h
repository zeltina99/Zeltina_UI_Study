// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenuWidget.generated.h"

class UButton;

/**
 * @brief 메뉴 선택 이벤트를 전달하기 위한 델리게이트
 * @param MenuName 선택된 메뉴의 이름 (FName)
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuSelected, FName, MenuName);	

/**
 * @class ULobbyMenuWidget
 * @brief 로비 우측의 메인 메뉴 버튼들(스테이지, 상점, 캐릭터 등)을 관리하는 위젯입니다.
 * @note 버튼 클릭 시 직접 로직을 수행하지 않고, OnMenuSelected 델리게이트를 통해 상위 위젯으로 이벤트를 전파합니다.
 */

UCLASS()
class UI_TEST_API ULobbyMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 외부에서 구독 가능한 메뉴 선택 이벤트.
	 */
	UPROPERTY(BlueprintAssignable, Category = "UI|Event")
	FOnMenuSelected OnMenuSelected;

	/**
	 * @brief 스테이지(월드맵) 위젯 클래스입니다. (WBP_WorldMap 할당)
	 * @details 버튼 클릭 시 이 클래스를 기반으로 위젯을 생성합니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSubclassOf<UUserWidget> StageMapClass = nullptr;

protected:
	virtual void NativeConstruct() override;

private:
#pragma region 메인 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SummonBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PartyBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EnhanceBtn;
#pragma endregion

	/**
	 * @brief 생성된 월드맵 위젯의 인스턴스를 저장하는 포인터입니다.
	 * @details 매번 CreateWidget 하지 않고, 한 번 만들면 재사용합니다.
	 */
	UPROPERTY()
	TObjectPtr<UUserWidget> StageMapInstance = nullptr;

#pragma region 내부 클릭 핸들러 (Delegate Broadcast용)
	UFUNCTION() void OnStageClicked();
	UFUNCTION() void OnSummonClicked();
	UFUNCTION() void OnPartyClicked();
	UFUNCTION() void OnEnhanceClicked();
#pragma endregion

};
