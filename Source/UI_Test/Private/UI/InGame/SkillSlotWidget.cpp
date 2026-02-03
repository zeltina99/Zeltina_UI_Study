// Source/UI_Test/Private/UI/InGame/SkillSlotWidget.cpp

#include "UI/InGame/SkillSlotWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#pragma region 초기화 및 설정

void USkillSlotWidget::InitializeSkill(UTexture2D* IconTexture, float CooldownTime)
{
	if (IconTexture && IconImage)
	{
		IconImage->SetBrushFromTexture(IconTexture);
	}

	MaxCooldown = CooldownTime;
	CurrentCooldown = 0.0f;
	bIsCoolingDown = false;

	if (CooldownBar)
	{
		CooldownBar->SetPercent(0.0f);
		CooldownBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillSlotWidget::StartCooldown()
{
	if (MaxCooldown <= 0.0f) return;

	bIsCoolingDown = true;
	CurrentCooldown = MaxCooldown;

	if (CooldownBar)
	{
		CooldownBar->SetVisibility(ESlateVisibility::Visible);
	}
}

#pragma endregion 초기화 및 설정

void USkillSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsCoolingDown)
	{
		UpdateCooldownVisual(InDeltaTime);
	}
}

#pragma region 내부 로직

void USkillSlotWidget::UpdateCooldownVisual(float DeltaTime)
{
	CurrentCooldown -= DeltaTime;

	if (CurrentCooldown <= 0.0f)
	{
		// 쿨타임 종료
		CurrentCooldown = 0.0f;
		bIsCoolingDown = false;

		if (CooldownBar)
		{
			CooldownBar->SetPercent(0.0f);
			CooldownBar->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		// 진행률 갱신
		if (CooldownBar)
		{
			float Percent = CurrentCooldown / MaxCooldown;
			CooldownBar->SetPercent(Percent);
		}
	}
}

#pragma endregion 내부 로직