// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Summon/SummonPopupWidget.h"
#include "UI/Summon/SummonTabWidget.h"
#include "UI/Summon/SummonActionWidget.h"
#include "UI/Summon/SummonBannerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controller/LobbyPlayerController.h"
#include "Component/GachaComponent.h"

#pragma region 초기화

void USummonPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 1. 하위 위젯(부품)들과 이벤트 연결 (Wiring)
	if (WBP_SummonTab)
	{
		WBP_SummonTab->OnTabChanged.AddDynamic(this, &USummonPopupWidget::HandleTabChanged);
	}

	if (WBP_SummonAction)
	{
		WBP_SummonAction->OnSummonRequest.AddDynamic(this, &USummonPopupWidget::HandleSummonRequest);
	}

	// 2. 공통 버튼 연결
	if (BtnClose)
	{
		BtnClose->OnClicked.AddDynamic(this, &USummonPopupWidget::OnClickClose);
	}

	// 3. 로직 컴포넌트 캐싱 (최적화)
	if (APlayerController* PC = GetOwningPlayer())
	{
		CachedGachaComp = PC->FindComponentByClass<UGachaComponent>();
	}
}

void USummonPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 화면이 열릴 때 초기 상태 리셋
	CurrentTab = EGachaType::Character;

	// 하위 위젯들도 초기 상태로 동기화
	if (WBP_SummonTab)
	{
		WBP_SummonTab->SetSelectedTab(CurrentTab);
	}

	UpdateAllViews();
}

#pragma endregion 초기화

#pragma region 이벤트 핸들러

void USummonPopupWidget::HandleTabChanged(EGachaType NewType)
{
	// [최적화] 변경사항이 없으면 무시
	if (CurrentTab == NewType)
	{
		return;
	}

	CurrentTab = NewType;
	UpdateAllViews(); // 탭이 바뀌었으니 화면 전체 갱신
}

void USummonPopupWidget::HandleSummonRequest(int32 Count)
{
	if (CachedGachaComp)
	{
		// 중재자 역할: ActionWidget의 요청(Count)에 현재 상태(Tab)를 더해서 컴포넌트로 전달
		CachedGachaComp->RequestSummon(Count, CurrentTab);

		// 소환 후 재화 갱신
		UpdateCurrencyDisplay();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ [SummonPopup] GachaComponent is Missing!"));
	}
}

void USummonPopupWidget::OnClickClose()
{
	// [네비게이션 규칙] 컨트롤러를 통해 화면 전환
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->ShowScreen(TEXT("Main"));
	}
}

#pragma endregion 이벤트 핸들러

#pragma region 화면 갱신

void USummonPopupWidget::UpdateAllViews()
{
	// 1. 배너 위젯 갱신 (이미지, 타이틀, 천장)
	if (WBP_SummonBanner)
	{
		WBP_SummonBanner->UpdateBannerView(CurrentTab);

		// 천장 정보는 컴포넌트에서 가져옴 (데이터 바인딩)
		if (CachedGachaComp)
		{
			// TODO: GachaComponent에 GetMaxPity() 등이 구현되어 있다고 가정
			int32 CurrentPity = CachedGachaComp->GetCurrentPityCount();
			WBP_SummonBanner->UpdatePityText(CurrentPity, 50);
		}
	}

	// 2. 액션 위젯 갱신 (비용)
	if (WBP_SummonAction)
	{
		// 임시 하드코딩된 비용 (나중엔 테이블에서 로드)
		WBP_SummonAction->UpdateCostText(160, 1600);
	}

	// 3. 재화 정보 갱신
	UpdateCurrencyDisplay();
}

void USummonPopupWidget::UpdateCurrencyDisplay()
{
	if (TextCurrentGem)
	{
		// TODO: 실제 유저 데이터 연동 (GameInstance 등)
		int32 MyGem = 5000;
		TextCurrentGem->SetText(FText::AsNumber(MyGem));
	}
}

#pragma endregion 화면 갱신