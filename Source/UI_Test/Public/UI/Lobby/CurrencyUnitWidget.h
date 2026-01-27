// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrencyUnitWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * @class UCurrencyUnitWidget
 * @brief 재화 아이콘 1개와 수량 텍스트 1개를 관리하는 최소 단위 위젯 클래스입니다.
 * @note 이 위젯은 독립적으로	사용되지 않고, TopBarWidget 등의 자식으로 포함되어 사용됩니다.
 */
UCLASS()
class UI_TEST_API UCurrencyUnitWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	/**
	 * @brief 위젯 초기화 시 호출됩니다.
	 */
	virtual void NativeConstruct() override;

public:
	/**
	 * @brief 재화 아이콘과 수량을 설정합니다.
	 * \param Icon 변경할 아이콘 텍스쳐 (nullptr일 경우 변경하지 않음)
	 * \param Amount 표시할 재화의 수량
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Currency")
	void SetCurrencyData(UTexture2D* Icon, int32 Amount);

private:
	/**
	 * @brief 재화 아이콘을 표시하는 이미지 위젯
	 * @warning 에디터의 위젯 이름과 반드시 일치해야 합니다.
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CurrencyIcon = nullptr;

	/**
	 * @brief 재화 수량을 표시하는 텍스트 블록
	 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AmountText = nullptr;

};
