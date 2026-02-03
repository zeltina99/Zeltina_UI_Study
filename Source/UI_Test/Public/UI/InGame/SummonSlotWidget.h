// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "SummonSlotWidget.generated.h"

#pragma region 전방선언
class UImage;
class UTextBlock;
class UProgressBar;
class UTexture2D;
#pragma endregion 전방선언

/**
 * @class USummonSlotWidget
 * @brief 유닛 소환 버튼. 코스트 확인 및 쿨타임 표시.
 */
UCLASS()
class UI_TEST_API USummonSlotWidget : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
#pragma region 초기화
	UFUNCTION(BlueprintCallable, Category = "UI|Summon")
	void InitSummonSlot(UTexture2D* Icon, int32 Cost, float CooldownTime);
#pragma endregion 초기화

public:
#pragma region 상태 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|Summon")
	void UpdateCostState(int32 CurrentPlayerCost);

	UFUNCTION(BlueprintCallable, Category = "UI|Summon")
	void StartCooldown();
#pragma endregion 상태 업데이트

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void UpdateCooldown(float DeltaTime);

protected:
#pragma region UI 컴포넌트
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> UnitIcon = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> CostText = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UProgressBar> CooldownOverlay = nullptr;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> NotEnoughCostImg = nullptr;
#pragma endregion UI 컴포넌트

private:
	int32 RequiredCost = 0;
	float MaxCooldown = 0.0f;
	float CurrentCooldown = 0.0f;
	bool bIsCoolingDown = false;
};
