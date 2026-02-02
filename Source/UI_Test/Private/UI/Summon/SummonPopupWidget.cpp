// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Summon/SummonPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Controller/LobbyPlayerController.h" // [Navigation Rule] 필수
#include "Component/GachaComponent.h"         // [Logic] 필수

#pragma region 초기화

void USummonPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 1. 탭 버튼 바인딩
	if (BtnTabCharacter) BtnTabCharacter->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickTabCharacter);
	if (BtnTabWeapon)    BtnTabWeapon->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickTabWeapon);

	// 2. 액션 버튼 바인딩
	if (BtnSingleSummon) BtnSingleSummon->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickSingleSummon);
	if (BtnMultiSummon)  BtnMultiSummon->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickMultiSummon);
	if (BtnClose)        BtnClose->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickClose);

	// 3. 컴포넌트 캐싱 (최적화)
	if (APlayerController* PC = GetOwningPlayer())
	{
		CachedGachaComp = PC->FindComponentByClass<UGachaComponent>();
	}
}

void USummonPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// UI가 켜질 때 기본 상태로 리셋
	CurrentTab = EGachaType::Character;

	UpdateView();         // 탭 UI 갱신
	UpdateCurrencyInfo(); // 재화 정보 갱신
}

#pragma endregion

#pragma region 이벤트 핸들러

void USummonPopupWidget::OnClickTabCharacter()
{
	if (CurrentTab == EGachaType::Character) return; // 최적화: 이미 선택된 탭 무시

	CurrentTab = EGachaType::Character;
	UpdateView();
}

void USummonPopupWidget::OnClickTabWeapon()
{
	if (CurrentTab == EGachaType::Weapon) return;

	CurrentTab = EGachaType::Weapon;
	UpdateView();
}

void USummonPopupWidget::OnClickSingleSummon()
{
	if (CachedGachaComp)
	{
		// [FIX] 두 번째 인자로 현재 탭(CurrentTab)을 넘겨줍니다.
		// (1회 소환, 캐릭터/무기 타입)
		CachedGachaComp->RequestSummon(1, CurrentTab);

		UpdateCurrencyInfo(); // 소모 후 재화 갱신
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ [SummonPopup] GachaComponent is nullptr!"));
	}
}

void USummonPopupWidget::OnClickMultiSummon()
{
	if (CachedGachaComp)
	{
		// [FIX] 여기도 마찬가지로 2개를 넘깁니다.
		// (10회 소환, 캐릭터/무기 타입)
		CachedGachaComp->RequestSummon(10, CurrentTab);

		UpdateCurrencyInfo();
	}
}

void USummonPopupWidget::OnClickClose()
{
	// [Zeltina Rule] Navigation via Controller
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(TEXT("Main"));
	}
	else
	{
		// Fallback (Should rarely happen)
		RemoveFromParent();
	}
}

#pragma endregion

#pragma region UI 로직

void USummonPopupWidget::UpdateView()
{
	// 1. 배너 타이틀 및 이미지 변경 (Data-Driven: 테이블에서 가져오는 것이 좋음)
	FText TitleText;
	if (CurrentTab == EGachaType::Character)
	{
		TitleText = FText::FromString(TEXT("캐릭터 픽업 소환"));
		// 버튼 상태: 선택된 탭은 비활성화(눌린 느낌), 나머지는 활성화
		if (BtnTabCharacter) BtnTabCharacter->SetIsEnabled(false);
		if (BtnTabWeapon)    BtnTabWeapon->SetIsEnabled(true);
	}
	else
	{
		TitleText = FText::FromString(TEXT("무기 픽업 소환"));
		if (BtnTabCharacter) BtnTabCharacter->SetIsEnabled(true);
		if (BtnTabWeapon)    BtnTabWeapon->SetIsEnabled(false);
	}

	if (TextBannerTitle) TextBannerTitle->SetText(TitleText);

	// 2. 비용 텍스트 갱신
	if (TextSingleCost) TextSingleCost->SetText(FText::AsNumber(COST_SINGLE));
	if (TextMultiCost)  TextMultiCost->SetText(FText::AsNumber(COST_MULTI));
}

void USummonPopupWidget::UpdateCurrencyInfo()
{
	// 1. 보유 재화 갱신 (임시 Mock Data -> 실제로는 GameInstance/PlayerState에서 로드)
	int32 CurrentGem = 5000;
	if (TextCurrentGem)
	{
		TextCurrentGem->SetText(FText::AsNumber(CurrentGem));
	}

	// 2. 천장 카운트 갱신
	if (CachedGachaComp && TextPityCount)
	{
		// 예: Component에서 Getter로 가져오기 (캡슐화)
		// int32 Pity = CachedGachaComp->GetCurrentPityCount();
		// TextPityCount->SetText(FText::Format(FText::FromString(TEXT("천장까지 {0}회")), 50 - Pity));
		TextPityCount->SetText(FText::FromString(TEXT("전설 확정까지 50회"))); // 임시
	}
}

#pragma endregion