// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGame/SkillSlotWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#pragma region 초기화

void USkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 바인딩
	if (SkillBtn)
	{
		SkillBtn->OnClicked.AddDynamic(this, &USkillSlotWidget::OnSkillButtonClicked);
	}

	// 초기 상태: 쿨타임 없음, 바 숨김
	if (CooldownBar) CooldownBar->SetVisibility(ESlateVisibility::Hidden);
	if (CooldownText) CooldownText->SetVisibility(ESlateVisibility::Hidden);
}

void USkillSlotWidget::InitializeSkill(UTexture2D* IconTexture, float InMaxCooldown)
{
	// 1. 아이콘 설정 (데이터 드라이븐)
	if (IconImage)
	{
		if (IconTexture)
		{
			IconImage->SetBrushFromTexture(IconTexture);
			IconImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			// 텍스처가 없으면 숨기거나 기본 이미지 처리
			// IconImage->SetVisibility(ESlateVisibility::Hidden); 
		}
	}

	// 2. 쿨타임 데이터 설정
	MaxCooldown = InMaxCooldown;
	CurrentCooldown = 0.0f;
	bIsCoolingDown = false;

	// 3. UI 리셋
	if (CooldownBar)
	{
		CooldownBar->SetPercent(0.0f);
		CooldownBar->SetVisibility(ESlateVisibility::Hidden);
	}
	if (CooldownText)
	{
		CooldownText->SetVisibility(ESlateVisibility::Hidden);
	}

	// 활성화 상태로 초기화
	SetSlotEnabled(true);
}

void USkillSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 최적화: 쿨타임 중일 때만 연산 수행
	if (bIsCoolingDown)
	{
		UpdateCooldownVisual(InDeltaTime);
	}
}

#pragma endregion 초기화

#pragma region 동작 제어

void USkillSlotWidget::StartCooldown()
{
	if (MaxCooldown <= KINDA_SMALL_NUMBER) return; // 쿨타임이 0이면 무시

	bIsCoolingDown = true;
	CurrentCooldown = MaxCooldown;

	// UI 켜기
	if (CooldownBar)
	{
		CooldownBar->SetVisibility(ESlateVisibility::Visible);
		CooldownBar->SetPercent(1.0f);
	}
	if (CooldownText)
	{
		CooldownText->SetVisibility(ESlateVisibility::Visible);
	}

	// 쿨타임 도는 동안 버튼 비활성화 (선택 사항)
	SetSlotEnabled(false);
}

void USkillSlotWidget::SetSlotEnabled(bool bIsEnable)
{
	if (SkillBtn)
	{
		SkillBtn->SetIsEnabled(bIsEnable);
	}

	// 비활성 시 아이콘을 회색조로 바꾸는 로직을 여기에 추가할 수 있음
}

#pragma endregion 동작 제어

#pragma region 내부 로직

void USkillSlotWidget::UpdateCooldownVisual(float DeltaTime)
{
	CurrentCooldown -= DeltaTime;

	if (CurrentCooldown <= 0.0f)
	{
		// 쿨타임 종료
		CurrentCooldown = 0.0f;
		bIsCoolingDown = false;

		// UI 숨기기
		if (CooldownBar) CooldownBar->SetVisibility(ESlateVisibility::Hidden);
		if (CooldownText) CooldownText->SetVisibility(ESlateVisibility::Hidden);

		// 버튼 다시 활성화
		SetSlotEnabled(true);
	}
	else
	{
		// 1. 프로그레스 바 갱신
		if (CooldownBar)
		{
			float Percent = CurrentCooldown / MaxCooldown;
			CooldownBar->SetPercent(Percent);
		}

		// 2. 남은 시간 텍스트 갱신 (소수점 1자리까지)
		if (CooldownText)
		{
			// FText 최적화를 위해 FNumberFormattingOptions 사용 가능
			CooldownText->SetText(FText::AsNumber(CurrentCooldown));
		}
	}
}

void USkillSlotWidget::OnSkillButtonClicked()
{
	// 쿨타임 중이면 클릭 무시 (이중 안전장치)
	if (bIsCoolingDown) return;

	// 외부(ActionPanel 등)에 이벤트 전파 로직 필요
	// 예: OnSlotClicked.Broadcast(); 
	// 혹은 상위 패널이 이 버튼의 OnClicked를 직접 바인딩해서 쓸 수도 있음.

	UE_LOG(LogTemp, Log, TEXT("[SkillSlot] Button Clicked!"));
}

#pragma endregion 내부 로직

