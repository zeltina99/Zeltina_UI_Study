// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Summon/SummonTabWidget.h"
#include "Components/Button.h"

#pragma region Initialization
void USummonTabWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 캐릭터 탭 버튼 바인딩
	if (BtnTabCharacter)
	{
		BtnTabCharacter->OnClicked.AddDynamic(this, &USummonTabWidget::OnClickCharacter);
	}

	// 무기 탭 버튼 바인딩
	if (BtnTabWeapon)
	{
		BtnTabWeapon->OnClicked.AddDynamic(this, &USummonTabWidget::OnClickWeapon);
	}
}
#pragma endregion 초기화

#pragma region Public API
void USummonTabWidget::SetSelectedTab(EGachaType NewType)
{
	// 시각적 피드백: 선택된 탭은 비활성화(Disabled)하여 '눌려있는 상태'처럼 보이게 함
	// 선택되지 않은 탭은 활성화(Enabled)하여 '누를 수 있는 상태'로 둠

	if (BtnTabCharacter)
	{
		// 캐릭터 탭이면 비활성(false), 아니면 활성(true)
		BtnTabCharacter->SetIsEnabled(NewType != EGachaType::Character);
	}

	if (BtnTabWeapon)
	{
		// 무기 탭이면 비활성(false), 아니면 활성(true)
		BtnTabWeapon->SetIsEnabled(NewType != EGachaType::Weapon);
	}
}
#pragma endregion 공개 API

#pragma region Event Handlers
void USummonTabWidget::OnClickCharacter()
{
	// 이미 비활성화(선택됨) 상태라면 굳이 로직을 실행하지 않음 (최적화)
	if (BtnTabCharacter && !BtnTabCharacter->GetIsEnabled())
	{
		return;
	}

	// 1. 상태 변경 (UI 갱신)
	SetSelectedTab(EGachaType::Character);

	// 2. 상위 위젯에 알림
	if (OnTabChanged.IsBound())
	{
		OnTabChanged.Broadcast(EGachaType::Character);
	}
}

void USummonTabWidget::OnClickWeapon()
{
	// 이미 비활성화(선택됨) 상태라면 로직 스킵
	if (BtnTabWeapon && !BtnTabWeapon->GetIsEnabled())
	{
		return;
	}

	// 1. 상태 변경 (UI 갱신)
	SetSelectedTab(EGachaType::Weapon);

	// 2. 상위 위젯에 알림
	if (OnTabChanged.IsBound())
	{
		OnTabChanged.Broadcast(EGachaType::Weapon);
	}
}
#pragma endregion 이벤트 핸들러