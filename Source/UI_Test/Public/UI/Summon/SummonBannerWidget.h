// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Data/GachaStructs.h"
#include "SummonBannerWidget.generated.h"

#pragma region 전방선언
class UImage;
class UTextBlock;
class UTexture2D;
#pragma endregion 전방선언

/**
 * @class USummonBannerWidget
 * @brief 가챠 배너 이미지와 천장(Pity) 정보를 표시하는 위젯. [SRP 준수]
 * @details
 * - 상위 위젯으로부터 현재 가챠 타입(Character/Weapon)을 받아 배너 이미지와 타이틀을 갱신한다.
 * - 천장 카운트 데이터를 받아 텍스트를 갱신한다.
 * - 철저하게 '보여주는 역할(View)'만 수행하며 로직을 포함하지 않는다.
 */
UCLASS()
class UI_TEST_API USummonBannerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
#pragma region 초기화
	virtual void NativeOnInitialized() override;
#pragma endregion 초기화

public:
#pragma region 공개 API
	/**
	 * @brief 현재 선택된 가챠 타입에 맞춰 배너 뷰를 갱신한다.
	 * @details (Data-Driven) 추후에는 테이블에서 이미지 리소스를 로드하는 방식으로 확장 가능.
	 * @param TabType 변경된 가챠 타입
	 */
	UFUNCTION(BlueprintCallable, Category = "Summon|View")
	void UpdateBannerView(EGachaType TabType);

	/**
	 * @brief 천장 카운트 텍스트를 갱신한다.
	 * @param CurrentPity 현재 쌓인 스택
	 * @param MaxPity 확정 천장 횟수
	 */
	UFUNCTION(BlueprintCallable, Category = "Summon|View")
	void UpdatePityText(int32 CurrentPity, int32 MaxPity);
#pragma endregion 공개 API

protected:
#pragma region 바인드 위젯
	/** @brief 픽업 배너 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImgBanner = nullptr;

	/** @brief 배너 타이틀 (예: "캐릭터 픽업 소환") */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBannerTitle = nullptr;

	/** @brief 천장 카운트 표시 (예: "전설 확정까지 50회") */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextPityCount = nullptr;
#pragma endregion 바인드 위젯

protected:
#pragma region 데이터 리소스 (Data-Driven)
	/** * @brief 캐릭터 픽업 배너 텍스처 (블루프린트에서 할당).
	 * @note 실제로는 DataTable에서 로드하는 것이 이상적이나, UI 테스트를 위해 BP 설정 허용.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summon|Resource")
	TObjectPtr<UTexture2D> CharacterBannerTexture = nullptr;

	/** @brief 무기 픽업 배너 텍스처 (블루프린트에서 할당) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Summon|Resource")
	TObjectPtr<UTexture2D> WeaponBannerTexture = nullptr;
#pragma endregion 데이터 리소스
};
