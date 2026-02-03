
#include "UI/InGame/InGameHUDWidget.h"
#include "Components/TextBlock.h"

#pragma region 초기화

void UInGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

#pragma endregion 초기화

#pragma region 데이터 분배

void UInGameHUDWidget::UpdateGameState(float RemainTime, int32 CurrentCost, int32 MaxCost)
{
	// 1. 타이머 갱신 (직접 관리)
	if (TimerText)
	{
		int32 Min = (int32)RemainTime / 60;
		int32 Sec = (int32)RemainTime % 60;
		TimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Min, Sec)));
	}

	// 2. 소환 패널에게 데이터 전달 (위임)
	if (SummonPanel)
	{
		SummonPanel->UpdateCostStatus(CurrentCost, MaxCost);
	}
}

void UInGameHUDWidget::UpdatePlayerStatus(int32 CharIndex, float HP, float MaxHP)
{
	// 파티 패널에게 데이터 전달 (위임)
	if (PartyPanel)
	{
		// 임시로 MP는 100으로 고정하여 전달 (추후 확장 가능)
		PartyPanel->UpdateMemberStatus(CharIndex, HP, MaxHP, 100.0f, 100.0f);
	}
}

#pragma endregion 데이터 분배