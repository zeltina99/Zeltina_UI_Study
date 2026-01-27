// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyTopBarWidget.generated.h"

class UCurrencyUnitWidget;
class UButton;

/**
 * @class ULobbyTopBarWidget
 * @brief 로비 상단에 위치하여 골드, 쥬얼 등의 재화 정보와 설정 버튼을 포함하는 위젯입니다.
 * @details CurrencyUnitWidget 인스턴스를 자식으로 가집니다.
 */
UCLASS()
class UI_TEST_API ULobbyTopBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	/**
	 * @brief 상단바의 모든 재화 정보를 갱신합니다.
	 * @param Gold 현재 보유한 골드량
	 * @param Gem 현재 보유한 쥬얼량
	 */
	UFUNCTION(BlueprintCallable, Category = "UI|Lobby")
	void UpdateTopBarInfo(int32 Gold, int32 Gem);

private:
	/** @brief 골드 아이콘 텍스처 (에디터 할당용) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> GoldIconTexture = nullptr;

	/** @brief 젬 아이콘 텍스처 (에디터 할당용) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> GemIconTexture = nullptr;

	/** @brief 골드 표시용 유닛 위젯 (BP에서 WBP_CurrencyUnit을 배치하고 이름을 맞춰야 함) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCurrencyUnitWidget> GoldUnitWidget = nullptr;

	/** @brief 쥬얼 표시용 유닛 위젯 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCurrencyUnitWidget> GemUnitWidget = nullptr;

	/** @brief 환경설정 버튼 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingBtn = nullptr;

	/** @brief 설정 버튼 클릭 시 호출되는 핸들러 */
	UFUNCTION()
	void OnSettingClicked();
	
};
