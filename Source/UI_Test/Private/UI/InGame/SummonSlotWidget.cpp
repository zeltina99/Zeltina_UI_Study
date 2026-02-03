// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/SummonSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#pragma region 초기화

void USummonSlotWidget::InitSummonSlot(UTexture2D* Icon, int32 Cost, float CooldownTime)
{
	if (UnitIcon && Icon) UnitIcon->SetBrushFromTexture(Icon);

	RequiredCost = Cost;
	MaxCooldown = CooldownTime;

	if (CostText) CostText->SetText(FText::AsNumber(Cost));

	if (CooldownOverlay)
	{
		CooldownOverlay->SetPercent(0.0f);
		CooldownOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}

#pragma endregion 초기화

void USummonSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bIsCoolingDown) UpdateCooldown(InDeltaTime);
}

#pragma region 상태 업데이트

void USummonSlotWidget::UpdateCostState(int32 CurrentPlayerCost)
{
	if (bIsCoolingDown) return; // 쿨타임 중이면 무시

	bool bCanAfford = (CurrentPlayerCost >= RequiredCost);
	SetIsEnabled(bCanAfford);

	if (NotEnoughCostImg)
	{
		NotEnoughCostImg->SetVisibility(bCanAfford ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}

void USummonSlotWidget::StartCooldown()
{
	if (MaxCooldown <= 0.0f) return;
	bIsCoolingDown = true;
	CurrentCooldown = MaxCooldown;
	SetIsEnabled(false);

	if (CooldownOverlay) CooldownOverlay->SetVisibility(ESlateVisibility::Visible);
}

void USummonSlotWidget::UpdateCooldown(float DeltaTime)
{
	CurrentCooldown -= DeltaTime;

	if (CurrentCooldown <= 0.0f)
	{
		bIsCoolingDown = false;
		CurrentCooldown = 0.0f;
		if (CooldownOverlay) CooldownOverlay->SetVisibility(ESlateVisibility::Hidden);
		// 상태 갱신은 다음 틱의 UpdateCostState에서 처리됨
	}
	else
	{
		if (CooldownOverlay) CooldownOverlay->SetPercent(CurrentCooldown / MaxCooldown);
	}
}

#pragma endregion 상태 업데이트