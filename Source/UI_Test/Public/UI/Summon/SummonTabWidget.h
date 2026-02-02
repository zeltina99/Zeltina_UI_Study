// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Data/GachaStructs.h"
#include "SummonTabWidget.generated.h"

#pragma region 전방 선언
class UButton;
#pragma endregion

/**
 * @brief 탭 변경 이벤트 델리게이트
 * @param NewType 변경된 가챠 타입 (캐릭터 / 무기)
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabChanged, EGachaType, NewType);

/**
 * @class USummonTabWidget
 * @brief 소환 화면의 좌측 탭(카테고리 선택)을 전담하는 위젯.
 * @details
 * - 버튼 클릭 입력을 받아 현재 탭 상태를 변경한다.
 * - 변경된 상태를 델리게이트(OnTabChanged)를 통해 상위 위젯에 알린다.
 * - 선택된 탭은 비활성화(Disabled) 처리하여 시각적 피드백을 제공한다.
 */

UCLASS()
class UI_TEST_API USummonTabWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
#pragma region 초기화
	/**
	 * @brief 위젯 초기화 (버튼 바인딩 수행)
	 */
	virtual void NativeOnInitialized() override;
#pragma endregion

public:
#pragma region Public API
	/**
	 * @brief 외부에서 탭을 강제로 선택할 때 사용 (초기화 등).
	 * @param NewType 선택할 탭의 종류
	 */
	UFUNCTION(BlueprintCallable, Category = "Summon|Tab")
	void SetSelectedTab(EGachaType NewType);
#pragma endregion

protected:
#pragma region 이벤트 핸들러
	/**
	 * @brief 캐릭터 탭 버튼 클릭 시 호출.
	 */
	UFUNCTION()
	void OnClickCharacter();

	/**
	 * @brief 무기 탭 버튼 클릭 시 호출.
	 */
	UFUNCTION()
	void OnClickWeapon();
#pragma endregion

public:
#pragma region 델리게이트
	/** @brief 탭이 변경되었을 때 호출되는 이벤트 디스패처 */
	UPROPERTY(BlueprintAssignable, Category = "Summon|Events")
	FOnTabChanged OnTabChanged;
#pragma endregion

protected:
#pragma region 바인드 위젯
	/** @brief 캐릭터 소환 탭 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTabCharacter = nullptr;

	/** @brief 무기 소환 탭 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTabWeapon = nullptr;
#pragma endregion
};
