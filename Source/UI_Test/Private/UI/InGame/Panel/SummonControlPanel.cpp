// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/Panel/SummonControlPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#pragma region 초기화

void USummonControlPanel::NativeConstruct()
{
	Super::NativeConstruct();

	SlotsArray.Empty();
	if (SummonSlot_1) SlotsArray.Add(SummonSlot_1);
	if (SummonSlot_2) SlotsArray.Add(SummonSlot_2);
	if (SummonSlot_3) SlotsArray.Add(SummonSlot_3);
	if (SummonSlot_4) SlotsArray.Add(SummonSlot_4);
	if (SummonSlot_5) SlotsArray.Add(SummonSlot_5);
}

#pragma endregion 초기화

#pragma region 데이터 업데이트

void USummonControlPanel::UpdateCostStatus(int32 CurrentCost, int32 MaxCost)
{
	// 1. 코스트 바
	if (CostBar && MaxCost > 0)
	{
		CostBar->SetPercent((float)CurrentCost / (float)MaxCost);
	}

	// 2. 텍스트 (예: 5 / 10)
	if (CostText)
	{
		CostText->SetText(FText::Format(FText::FromString(TEXT("{0} / {1}")), CurrentCost, MaxCost));
	}

	// 3. 슬롯 상태 갱신 (위임)
	for (auto& SummonSlot : SlotsArray)
	{
		if (SummonSlot) SummonSlot->UpdateCostState(CurrentCost);
	}
}

#pragma endregion 데이터 업데이트