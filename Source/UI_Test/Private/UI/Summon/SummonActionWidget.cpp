// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Summon/SummonActionWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#pragma region 초기화
void USummonActionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 1회 소환 버튼 바인딩
	if (BtnSingleSummon)
	{
		BtnSingleSummon->OnClicked.AddDynamic(this, &USummonActionWidget::OnClickSingle);
	}

	// 10회 소환 버튼 바인딩
	if (BtnMultiSummon)
	{
		BtnMultiSummon->OnClicked.AddDynamic(this, &USummonActionWidget::OnClickMulti);
	}
}
#pragma endregion 초기화

#pragma region 공개 API
void USummonActionWidget::UpdateCostText(int32 SingleCost, int32 MultiCost)
{
	// [최적화] 불필요한 FText 생성을 방지하기 위해 유효성 검사 선행
	if (TextSingleCost)
	{
		TextSingleCost->SetText(FText::AsNumber(SingleCost));
	}

	if (TextMultiCost)
	{
		TextMultiCost->SetText(FText::AsNumber(MultiCost));
	}
}
#pragma endregion 공개 API

#pragma region 이벤트 핸들러
void USummonActionWidget::OnClickSingle()
{
	// 상위 위젯에 '1회 소환' 요청 전파
	if (OnSummonRequest.IsBound())
	{
		OnSummonRequest.Broadcast(1);
	}
}

void USummonActionWidget::OnClickMulti()
{
	// 상위 위젯에 '10회 소환' 요청 전파
	if (OnSummonRequest.IsBound())
	{
		OnSummonRequest.Broadcast(10);
	}
}
#pragma endregion 이벤트 핸들러