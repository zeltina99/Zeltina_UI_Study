
#include "UI/InGame/CharacterStatusWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

#pragma region 초기화

void UCharacterStatusWidget::InitializeCharacter(UTexture2D* Portrait)
{
	if (PortraitImg)
	{
		if (Portrait) PortraitImg->SetBrushFromTexture(Portrait);
	}

	// 초기화
	UpdateStatus(100, 100, 100, 100);
	SetActiveState(false, false);
}

#pragma endregion 초기화

#pragma region 상태 업데이트

void UCharacterStatusWidget::UpdateStatus(float CurHP, float MaxHP, float CurMP, float MaxMP)
{
	if (HPBar && MaxHP > 0)
	{
		HPBar->SetPercent(CurHP / MaxHP);
	}
	if (MPBar && MaxMP > 0)
	{
		MPBar->SetPercent(CurMP / MaxMP);
	}
}

void UCharacterStatusWidget::SetActiveState(bool bIsActive, bool bIsDead)
{
	if (DeadIcon)
	{
		DeadIcon->SetVisibility(bIsDead ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}

	if (DimmedOverlay)
	{
		// 비활성 상태이거나 죽었으면 어둡게
		bool bShouldDim = !bIsActive || bIsDead;
		DimmedOverlay->SetVisibility(bShouldDim ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

#pragma endregion 상태 업데이트