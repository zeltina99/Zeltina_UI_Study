// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDetailWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

// 델리게이트 선언: 버튼 클릭 알림용
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDetailButtonEvent);

/**
 * @brief 상세 정보 패널을 담당하는 위젯 클래스.
 * * 캡슐화: UI 컴포넌트는 외부에서 접근 불가능하며, 오직 UpdateInfo 함수로만 제어됩니다.
 * * 최적화: 불필요한 렌더링 갱신을 막기 위해 데이터가 유효할 때만 UI를 갱신합니다.
 */
UCLASS()
class UI_TEST_API UInventoryDetailWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	/**
	 * @brief UI 정보를 갱신합니다.
	 * @param InData 표시할 아이템/캐릭터 데이터 (nullptr일 경우 숨김 처리)
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateInfo(class UInventoryItemData* InData);

	/** @brief 교체/장착 버튼이 클릭되었을 때 발동하는 이벤트 */
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnDetailButtonEvent OnSwapButtonClicked;

protected:
	/** @brief 내부 버튼 클릭 핸들러 */
	UFUNCTION()
	void HandleSwapButtonClicked();

protected:
	// ★ [수정] 배경 이미지는 코드로 안 건드립니다! (WBP에서 고정)
	// 대신 '내용물'을 담는 상자를 껐다 켰다 할 겁니다.

	/** @brief 텍스트와 버튼이 들어있는 컨테이너 (Overlay나 VerticalBox) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidget> ContentBox = nullptr;

	/** @brief 클릭했을 때 뜨는 연하늘색 블러 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> BlurImage = nullptr;

	/** @brief 상세 설명 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DetailNameText = nullptr;

	/** @brief 교체 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BtnEquip = nullptr;
};
